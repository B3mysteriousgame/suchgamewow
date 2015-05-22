#include "patate.hpp"
#include "gamemanager.hpp"
#include "mouse.h"
#include "ball.hpp"
#include "barre.hpp"
#include <QDebug>

Patate::Patate(QGraphicsItem *parent)
    : Personnage(parent)
{
    _imgCpt = 0;
    _sens = Personnage::DROITE; // idle
    _speed = 2;
    _gm = GameManager::Instance();
    _fullhealth = 420;
    _actualhealth = _fullhealth;
    _def = 50;
    _xp = 0;
    _xpMax = 200;
    _lvl = 1;
    _atk = 100;
    _fullki = 100;
    _ki = _fullki;
    _fullmana = 240;
    _mana = _fullmana;
    _movin = false;
    _timout = 500;
    _timerKiCharg = new QTimer();
    _charginKi = false;

    _inventaire = new Inventaire();

    setPos(10, 20);
    setPixmap(QPixmap(":link/images/Sprites/patate/patateD1.png"));

    _sm = new SpriteManager(this, "patate", 4);

    QObject::connect(_gm, SIGNAL(chargeKiStarted()), this, SLOT(startKiCharge()));
    QObject::connect(_gm, SIGNAL(chargeKiStopped()), this, SLOT(stopKiCharge()));
    QObject::connect(_timerKiCharg, SIGNAL(timeout()), this, SLOT(rechargKi()));
}

/**
 * @brief Constructeur par copie ( pointeur vers l'objet patate a copié )
 * @param p (pointeur vers Objet patate a copier)
 */
/*
Patate::Patate(Patate *p)
    : Personnage(p->parentItem())
{
    _imgCpt = p->getImgCpt();
    _sprites = p->getSprites();
    _sens = p->getSens();
    _speed = p->getSpeed();
    _gm = NULL;
    _blockinCase = -1;

    setPixmap(p->pixmap());
    //show();
}
*/

int Patate::getImgCpt() const
{
    return _imgCpt;
}


void Patate::initStates()
{
}


QList<QString> Patate::getSprites() const
{
    return _sprites;
}

void Patate::test()
{
    static const int adjust = 1;
    QRectF rec = boundingRect();
    rec.setSize(QSize(rec.width() + adjust * 2, rec.height() + adjust * 2));
    rec.setX( rec.x() - adjust );
    rec.setY( rec.y() - adjust );
}

void Patate::advance(int)
{
    avancer(_sens);
}

void Patate::avancer(short sens)
{
    static short cpt = 1; // va de 1 a maxTour non compris (1 a 3)
    static const short maxTour = 7, maxSprite = 4;
    static MyView *view = GameManager::Instance()->getView();
    QString spritePAth = ":link/images/Sprites/link/link";
    //static short lastBlockinDir = -1;

    if(_gm == NULL)
        _gm = GameManager::Instance();

    if(sens != _sens) // si on change de sens
    {
        cpt = 1; // pour changer d'image apres
        _imgCpt = 0; // incremente apres, donc img 1 sera affichee
        _sens = sens; // on dit qu'on change de sens
    }

    if(_movin == false)
        _imgCpt = 0; // incr apres
    else
        ChangeSensEtDeplacement();

    if(cpt >= maxTour) // on repasse a 1
        cpt = 0;

    _gm->centerOnPatate();

    ++cpt;
}

void Patate::loseHealth(int degats)
{
    qreal pourcentage;
    Personnage::loseHealth(degats); // personnage test si targetable

    pourcentage = getPourcentageVie();
    //_gm->setViePatate(pourcentage/2);
    emit statChanged(pourcentage/2, "vie");
}

Patate::~Patate(){}

void Patate::attaque()
{
    if(_ki > 0)
    {
        if(_gm == NULL)
            _gm = GameManager::Instance();

        Ball *b = new Ball(this);

        _gm->addItemToScene(b);

        loseKi(5);
    }
}

/**
 * @brief S'assure que le patate est dans la vue,
 *  et la tp a l'oppose si elle depasse
 */
void Patate::stayInView()
{
    static QRectF viewRect;

    viewRect = GameManager::Instance()->getView()->getViewRect();
    // TODO: essayer de pas recup le rect a chaque tour

    if(y() > viewRect.bottomLeft().y())
        setPos(x(), viewRect.topRight().y());
    else
    {
        if(y() < viewRect.topRight().y())
            setPos(x(), viewRect.bottomLeft().y());
        else
        {
            if(x() > viewRect.bottomRight().x())
                setPos(viewRect.topLeft().x(), y());
            else
                if(x() < viewRect.topLeft().x())
                    setPos(viewRect.bottomRight().x(), y());
        }
    }
}

/**
 * @brief Scroll la vue si la patate sort des bords
 * @return le sens bloquant si la patate est aux limites de la scene,
 *  -1 sinon
 */
bool Patate::scrollView()
{
    static QRectF viewRect;
    static QRectF lastViewRect = GameManager::Instance()->getView()->getViewRect();
    //static bool viewScrolled = false;
    //qreal xx, yy;

    // permet de laisser un decalage avec les bords
    static const short offset = 2;

    viewRect = GameManager::Instance()->getView()->getViewRect();
    // TODO: essayer de pas recup le rect a chaque tour

    //xx = x();
    //yy = y();

    if(y() > lastViewRect.bottomRight().y() - offset ||
        y() < lastViewRect.topLeft().y() + offset ||
        x() > lastViewRect.bottomRight().x() - offset ||
        x() < lastViewRect.topLeft().x() + offset)
    {
        if(isNearSceneBorder()) // proche du bord
        {
            _blockinBorder = _sens; // on empeche de continuer par la
            //qWarning() << "Patate near border" << _sens;
        }
        else // ailleurs
        {
            GameManager::Instance()->scrollView(_sens); // on scroll

            viewRect = GameManager::Instance()->getView()->getViewRect();
            //viewScrolled = true;

            if(_blockinBorder != -1)
                _blockinBorder = -1;

            //qWarning() << "Scrolled towards" << _sens;
            GameManager::qSleep(250);
        }
    }

    return -1;
}

/**
 * @brief S'assure que le personnage ne depasse pas
 *  les bords de la scene
 *
 * not used
 */
void Patate::stayInScene()
{
    static const QRectF sceneRect = GameManager::Instance()->getScene()->sceneRect();

    if(y() > sceneRect.bottomLeft().y())
        setPos(x(), sceneRect.topRight().y());
    else
    {
        if(y() < sceneRect.topRight().y())
            setPos(x(), sceneRect.bottomLeft().y());
        else
        {
            if(x() > sceneRect.bottomRight().x())
                setPos(sceneRect.topLeft().x(), y());
            else
                if(x() < sceneRect.topLeft().x())
                    setPos(sceneRect.bottomRight().x(), y());
        }
    }
}

void Patate::handlePosLimits()
{
/*    if(_blockinBorder != _sens && _blockinCase != _sens)
        scrollView(_sens);
    else
        stayInScene();
*/}

/**
 * @brief Patate::isNearSceneBorder Verifie si on est proche d'une bordure de la scene
 *  en testant si on est contenu dans le rectangle de la scene (un peu plus petit)
 * @return vrai si proche d'un bord, faux sinon
 */
bool Patate::isNearSceneBorder() const
{
    static const short offset = 20;
    static const QRectF smallSceneRect = GameManager::Instance()->getScene()->sceneRect().adjusted(offset, offset, -2 * offset, -2 * offset);
    static bool cpt = true;

    if(cpt)
    {
        cpt = false;
        //qWarning() << "Patate::isNearSceneBorder ---> Rectangle:" << smallSceneRect;
    }
    else
    {
        //qWarning() << "Patate::isNearSceneBorder ---> Not close to bordas";
    }

    return !smallSceneRect.contains(this->boundingRect());
}

void Patate::setXp(const int xp)
{
    _xp = xp;
}

void Patate::addXp(const int xp)
{
    _xp += xp;
    //qWarning() << "XP now at" << _xp;

    if(_xp > _xpMax)
    {
        int diff = _xp - _xpMax;
        lvlUp();
        addXp(diff);
    }
}

/**
 * @brief Patate::rechargKi Remonte le ki de 1.
 *  Doit etre appellee toutes les 10eme de seconde tant que la touche
 *  de recharge est appuyee
 */
void Patate::rechargKi()
{
    //qWarning() << "Patate::rechargKi()";
    loseKi(-2. - 0.12 * _lvl);

    if(_charginKi)
    {
        _timerKiCharg->start(100);
        _charginKi = false;
    }
    else
    {
        _timerKiCharg->stop();
    }
}

void Patate::setCharginKi(bool is)
{
    _charginKi = is;

    if(is == true) // if now is chargin
    {
        //qWarning() << "ki charge STARTED";
        if(!_timerKiCharg->isActive())
            _timerKiCharg->start(100);
    }
    else // if ain't chargin no more
    {
        //qWarning() << "ki charge STOPPED";
        if(_timerKiCharg->isActive())
            _timerKiCharg->stop();
    }
}

void Patate::lvlUp()
{
    _lvl += 1;
    _xpMax += 200;
    _atk += 6;
    _def += 4;
    _fullki += 2 * _lvl;

    if(_lvl % 2 == 0) // lvl paire
        _fullhealth += 28;
    else
        _fullmana += 24;

    _gm->patateLvlUp();
    //qWarning() << "Level up! Now lvl" << _lvl;
}

void Patate::loseMana(int mana)
{
   //qWarning() << "looseMana: manaToLose:mana:fullmana:" << mana << ":" << _mana << ":" << _fullmana;
    _mana -= mana;

    if(_mana < 0)
        _mana = 0;

    //qWarning() << "looseMana: pourcentage:mana:fullmana:" << _mana * 100 / _fullmana << ":" << _mana << ":" << _fullmana;
    //_gm->setManaPatate(_mana * 100 / _fullmana);
    emit statChanged(_mana * 100 / _fullmana, "mana");
}

void Patate::loseKi(qreal ki)
{
    //qWarning() << "KI" << ki;
    _ki -= ki;

    if(_ki < 0)
        _ki = 0;
    else if (_ki > _fullki)
        _ki = _fullki;

    //_gm->setKiPatate(_ki * 100 / _fullki);
    emit statChanged(_ki * 100 / _fullki, "ki");
}

void Patate::startKiCharge()
{
    if(!_timerKiCharg->isActive())
        _timerKiCharg->start(100);

    _charginKi = true;
    //qWarning() << "ki charge started";
}

void Patate::stopKiCharge()
{
    if(_timerKiCharg->isActive())
        _timerKiCharg->stop();

    _charginKi = false;

    //qWarning() << "ki charge stopped";
}

void Patate::Teleportation()
{
 if(_mana >= 5)
 {
    static EnnemyFactory* const ef = _gm->getEnnemyFactory();
    qreal ddx = 0, ddy = 0,offset = 1.1;
    int quickspeed = _speed * 20;

        switch (_sens)
        {
            case Personnage::DROITE:
                ddx += quickspeed * offset;
                break;
            case Personnage::GAUCHE:
                ddx += quickspeed * offset * -1.;
                break;
            case Personnage::BAS:
                ddy += quickspeed * offset;
                break;
            case Personnage::HAUT:
                ddy += quickspeed * offset * -1.;
                break;
            default:
                break;
        }

        QPointF arrive = QPointF(this->x() + ddx, this->y() + ddy);
        QList<Ennemy*> listeMichels = _gm->getEnnemyFactory()->getListMichel();

        foreach(Ennemy *simon, listeMichels)
        {
            QLineF dist = QLineF(simon->pos(),arrive);
            if(dist.length() <= 50)
            {
             qWarning() << "pos" << simon->pos();
             simon->moveBy(10,30);
             qWarning() << "posaprès" << simon->pos();

            }
        }
        moveBy(ddx, ddy);
        loseMana(5);
    }
}

void Patate::AfficheInventaire()
{
    _inventaire->show();
}

void Patate::addItemToInventaire(Arme *arme)
{
    _inventaire->addItem(arme);
}
