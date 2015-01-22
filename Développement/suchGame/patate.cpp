#include "patate.hpp"
#include "gamemanager.hpp"
#include "mouse.h"
#include <QDebug>

Patate::Patate(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    // ":/images/patate.png"
    // _sprites = QList<QString>();
    _sprites.append(":/images/Sprites/linkD1.png");
    _sprites.append(":/images/Sprites/linkD2.png");
    _sprites.append(":/images/Sprites/linkD3.png");
    _sprites.append(":/images/Sprites/linkD2.png");

    _imgCpt = 0;
    _sens = Patate::DROITE;

    setPixmap(QPixmap(":/images/Sprites/linkD1.png"));
}

Patate::Patate(Patate *p)
    : QGraphicsPixmapItem(p->parentItem())
{
    _imgCpt = p->getImgCpt();
    _sprites = p->getSprites();
    _sens = p->getSens();

    setPixmap(p->pixmap());
    //show();
}

int Patate::getImgCpt() const
{
    return _imgCpt;
}

int Patate::getSens() const
{
    return _sens;
}

void Patate::setSens(const short sens)
{
    if(sens != 0 && sens != 1 && sens != 2 && sens != 3 )
    {
        qDebug() << "Erreur valeur sens.";
        throw;
    }
    else
        _sens = sens;
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

    //QGraphicsEllipseItem ell = QGraphicsEllipseItem(rec);

    //GameManager::Instance()->addItemToScene( ell );
}

void Patate::advance(int step)
{
    static short cpt = 1, maxTour = 4, maxSprite = 4;
    const qreal maxX = 435, maxY = 354;
    QString spritePAth = ":/images/Sprites/link";
    qreal ddx = 0, ddy = 0, offset = 0.9;

    //_sens = Patate::BAS;
    switch (_sens)
    {
        case Patate::DROITE:
            ddx += offset;
            spritePAth.append("D");
            break;
        case Patate::GAUCHE:
            ddx += offset * -1.;
            spritePAth.append("G");
            break;
        case Patate::BAS:
            ddy += offset;
            spritePAth.append("B");
            break;
        case Patate::HAUT:
            ddy += offset * -1.;
            spritePAth.append("H");
            break;
        default:
            break;
    }

    if(cpt >= maxTour) // on repasse a 0
        cpt = 0; // incremente apres donc = 1 la prochaine fois
    else
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
    //GameManager.Instance()->setText(QString("pos: ").append(QString::number(x())).append(" - ").append(QString::number(y())));

    // test collision
    QList<QGraphicsItem*> listCollides = collidingItems();
    if(listCollides.length() > 0)
    {
        foreach (QGraphicsItem *item, listCollides)
        {
            if(item->type() == Mouse::Type)
                GameManager::Instance()->removeItem(item);
        }
    }

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

QPointF Patate::center() const
{
    return QPointF(boundingRect().x() + boundingRect().width() / 2,
                       boundingRect().y() + boundingRect().height() / 2 - 7);

}
*/
