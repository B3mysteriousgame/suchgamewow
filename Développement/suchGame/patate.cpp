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
    const qreal maxX = 435, maxY = 354;
    QString spritePAth = ":/images/Sprites/link";
    qreal ddx = 0, ddy = 0, offset = 1;

    if(sens != _sens) // si on change de sens
    {
        cpt = 1; // pour changer d'image
        _imgCpt = 0; // incremente apres, dond img 1 sera affichee

        _sens = sens; // on dit qu'on change de sens
    }

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

    if(cpt >= maxTour) // on repasse a 0
        cpt = 1; // incremente apres donc = 1 la prochaine fois

    if(cpt == 1) // on change l'image
    {
        _imgCpt += 1;

        if(_imgCpt > maxSprite)
            _imgCpt = 1;

        spritePAth.append(QString::number(_imgCpt));
        setPixmap(QPixmap(spritePAth));
    }

    moveBy(ddx, ddy);

    if(y() > maxY)
        setPos(x(), maxY * -1.);
    else
    {
        if(y() < maxY * -1.)
            setPos(x(), maxY);
        else
        {
            if(x() > maxX)
                setPos(maxX * -1., y());
            else
                if(x() < maxX * -1.)
                    setPos(maxX, y());
        }
    }

    qWarning() << "pos: " << x() << " - " << y();

    // test collision
    /*QList<QGraphicsItem*> listCollides = collidingItems();
    if(listCollides.length() > 0)
    {
        foreach (QGraphicsItem *item, listCollides)
        {
            if(item->type() == Mouse::Type)
                GameManager::Instance()->removeItem(item);
        }
    }*/

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
