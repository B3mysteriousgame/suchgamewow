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
    _gm = NULL;
    _fullhealth = 100;
    _actualhealth = _fullhealth;
    _def = 50;
    _xp = 0;
    _xpMax = 200;
    _lvl = 1;
    _atk = 48;
    _movin = false;

  /*  _barre = new Barre(true);
    QPointF lepoint = QPointF(GameManager::Instance()->getView()->getViewRect().width(),(0 + _barre->getHauteur()));
    _barre->setPos(lepoint); */

    setPos(10, 20);
    setPixmap(QPixmap(":link/images/Sprites/link/linkD1.png"));
    //initStates();

    _sm = new SpriteManager(this, "link", 4);
}

/**
 * @brief Constructeur par copie ( pointeur vers l'objet patate a copié )
 * @param p (pointeur vers Objet patate a copier)
 */
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

int Patate::getImgCpt() const
{
    return _imgCpt;
}


void Patate::initStates()
{
    /*
    GameManager *gm = GameManager::Instance();

    // passe au state quand il recoit un signal du gm
    sdroite.addTransition(gm, SIGNAL(downSignal()), &sbas);
    sdroite.addTransition(gm, SIGNAL(upSignal()), &shaut);
    sdroite.addTransition(gm, SIGNAL(leftSignal()), &sgauche);
    sdroite.addTransition(gm, SIGNAL(stopMovinSignal()), &sidle);

    sgauche.addTransition(gm, SIGNAL(downSignal()), &sbas);
    sgauche.addTransition(gm, SIGNAL(upSignal()), &shaut);
    sgauche.addTransition(gm, SIGNAL(rightSignal()), &sdroite);
    sgauche.addTransition(gm, SIGNAL(stopMovinSignal()), &sidle);

    shaut.addTransition(gm, SIGNAL(downSignal()), &sbas);
    shaut.addTransition(gm, SIGNAL(rightSignal()), &sdroite);
    shaut.addTransition(gm, SIGNAL(leftSignal()), &sgauche);
    shaut.addTransition(gm, SIGNAL(stopMovinSignal()), &sidle);

    sbas.addTransition(gm, SIGNAL(upSignal()), &shaut);
    sbas.addTransition(gm, SIGNAL(rightSignal()), &sdroite);
    sbas.addTransition(gm, SIGNAL(leftSignal()), &sgauche);
    sbas.addTransition(gm, SIGNAL(stopMovinSignal()), &sidle);

    sidle.addTransition(gm, SIGNAL(upSignal()), &shaut);
    sidle.addTransition(gm, SIGNAL(rightSignal()), &sdroite);
    sidle.addTransition(gm, SIGNAL(leftSignal()), &sgauche);
    sidle.addTransition(gm, SIGNAL(downSignal()), &sbas);
    // -----------------------------------------------

    // change the property
    shaut.assignProperty(this, "_sens", 1);
    sdroite.assignProperty(this, "_sens", 2);
    sbas.assignProperty(this, "_sens", 3);
    sgauche.assignProperty(this, "_sens", 0);
    // -------------------

    //QObject::connect(&sbas, SIGNAL(entered()), button, SLOT(showMaximized()));

    _stateMachine.addState(&shaut);
    _stateMachine.addState(&sbas);
    _stateMachine.addState(&sdroite);
    _stateMachine.addState(&sgauche);
    _stateMachine.addState(&sidle);

    _stateMachine.setInitialState(&sidle);
    */
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

    /*
    if(_blockinBorder != _sens)
    {
        moveBy(ddx, ddy);

        if(_blockinCase != lastBlockinDir)
            _blockinCase = -1; // pour pas rebloquer   
    }
    */

    //qWarning() << "pos: " << x() << " - " << y();

    if(cpt >= maxTour) // on repasse a 1
        cpt = 0;

    view->centerOn(this);

    ++cpt;
}

/*
QRectF Patate::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(x() - adjust, y() - adjust,
                  pixmap().width() + adjust * 2, pixmap().height() + adjust * 2);
}
QPainterPath Patate::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());

    return path;
}
void Patate::paint(QPainter *painter, const QStyleOptionGraphicsItem *sogi,
           QWidget *wid)
{

}
*/

Patate::~Patate(){}

void Patate::attaque()
{
    if(_gm == NULL)
        _gm = GameManager::Instance();

    Ball *b = new Ball(this);

    _gm->addItemToScene(b);
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

    /*
    // Verifie si on s'apprete a sortir de la scene
    // en testant si scrollView() a marcher ou non
    if(lastViewRect != viewRect)
    {
        lastViewRect = viewRect;
    }
    else if(lastViewRect == viewRect && viewScrolled == true)
    { // la patate s'apprete a sortir de la scene
        viewScrolled = false; // pour pas le retraiter la fois suivante
        return _sens;
    }
    */

    //viewScrolled = false;

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

void Patate::lvlUp()
{
    _lvl += 1;
    _xpMax += 200;
    _atk += 20;
    _def += 4;

    if(_lvl % 2 == 0) // lvl paire
        _fullhealth += 28;
    else
        _mana += 24;

    _gm->patateLvlUp();
    //qWarning() << "Level up! Now lvl" << _lvl;
}
