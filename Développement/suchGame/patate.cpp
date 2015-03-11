#include "patate.hpp"
#include "gamemanager.hpp"
#include "mouse.h"
#include "ball.hpp"
#include <QDebug>

Patate::Patate(QGraphicsItem *parent)
    : Personnage(parent)
{
    // ":/images/patate.png"
    // _sprites = QList<QString>();
    _sprites.append(":/images/Sprites/linkD1.png");
    _sprites.append(":/images/Sprites/linkD2.png");
    _sprites.append(":/images/Sprites/linkD3.png");
    _sprites.append(":/images/Sprites/linkD2.png");

    _imgCpt = 0;
    _sens = Patate::DROITE;
    _speed = 3;
    _gm = NULL;
    _fullhealth = 100;
    _actualhealth = _fullhealth;
    _resistance = 50;

    setPos(10, 20);
    setPixmap(QPixmap(":/images/Sprites/linkD1.png"));
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

void Patate::advance(int step){}

void Patate::avancer(short sens)
{
    static short cpt = 1; // va de 1 a maxTour non compris (1 a 3)
    static const short maxTour = 4, maxSprite = 4;
    static MyView *view = GameManager::Instance()->getView();
    QString spritePAth = ":/images/Sprites/link";
    qreal ddx = 0, ddy = 0, offset = 1;
    static short lastBlockinDir = -1;

    if(sens != _sens) // si on change de sens
    {
        cpt = 1; // pour changer d'image apres
        _imgCpt = 0; // incremente apres, dond img 1 sera affichee

        _sens = sens; // on dit qu'on change de sens

        /*
        if(_blockinCase != -1)
            _blockinCase = -1;
         */
    }
    else // sinon on test le scroll
    {
        /*
        lastBlockinDir = _blockinCase;
        _blockinCase = scrollView(lastBlockinDir);
        */
    }

    // on calcule la nouvelle valeur de x ou y en fonction du sens
    switch (_sens)
    {
        case Patate::DROITE:
            ddx += _speed * offset;
            spritePAth.append("D");
            break;
        case Patate::GAUCHE:
            ddx += _speed * offset * -1.;
            spritePAth.append("G");
            break;
        case Patate::BAS:
            ddy += _speed * offset;
            spritePAth.append("B");
            break;
        case Patate::HAUT:
            ddy += _speed * offset * -1.;
            spritePAth.append("H");
            break;
        default:
            break;
    }

    if(cpt >= maxTour) // on repasse a 1
        cpt = 1;

    if(cpt == 1) // on change l'image
    {
        _imgCpt += 1;

        if(_imgCpt > maxSprite)
            _imgCpt = 1;

        spritePAth.append(QString::number(_imgCpt));
        setPixmap(QPixmap(spritePAth));
    }

    moveBy(ddx, ddy);
    view->centerOn(this);

    /*
    if(_blockinBorder != _sens)
    {
        moveBy(ddx, ddy);

        if(_blockinCase != lastBlockinDir)
            _blockinCase = -1; // pour pas rebloquer   
    }
    */

    //qWarning() << "pos: " << x() << " - " << y();

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
bool Patate::scrollView(const short lastBlockinDir)
{
    static QRectF viewRect;
    static QRectF lastViewRect = GameManager::Instance()->getView()->getViewRect();
    static bool viewScrolled = false;
    qreal xx, yy;

    // permet de laisser un decalage avec les bords
    static const short offset = 2;

    viewRect = GameManager::Instance()->getView()->getViewRect();
    // TODO: essayer de pas recup le rect a chaque tour

    xx = x();
    yy = y();

    if(y() > lastViewRect.bottomRight().y() - offset ||
        y() < lastViewRect.topLeft().y() + offset ||
        x() > lastViewRect.bottomRight().x() - offset ||
        x() < lastViewRect.topLeft().x() + offset)
    {
        if(isNearSceneBorder()) // proche du bord
        {
            _blockinBorder = _sens; // on empeche de continuer par la
            qWarning() << "Patate near border" << _sens;
        }
        else // ailleurs
        {
            GameManager::Instance()->scrollView(_sens); // on scroll

            viewRect = GameManager::Instance()->getView()->getViewRect();
            //viewScrolled = true;

            if(_blockinBorder != -1)
                _blockinBorder = -1;

            qWarning() << "Scrolled towards" << _sens;
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
        qWarning() << "Patate::isNearSceneBorder ---> Rectangle:" << smallSceneRect;
    }
    else
    {
        qWarning() << "Patate::isNearSceneBorder ---> Not close to bordas";
    }

    return !smallSceneRect.contains(this->boundingRect());
}
