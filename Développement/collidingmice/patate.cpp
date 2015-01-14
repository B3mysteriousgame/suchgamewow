#include "patate.hpp"
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
    _sens = 0;

    setPixmap(QPixmap(":/images/Sprites/linkD1.png"));

    /*
    setPos(10, 10);

    show();
    */
}

Patate::Patate(Patate *p)
    : QGraphicsPixmapItem(p->parentItem())
{
    _imgCpt = p->getImgCpt();
    _sprites = p->getSprites();

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

void Patate::advance(int step)
{
    static short cpt = 0; // compteur de passage dans la fonction
    static const short tour = 3; // change le sprite 1 fois sur 5
    static const short nbSprite = 5;
    static const float offset = 0.5;
    float ddx = 0, ddy = 0;
    QString spritePath = ":/images/Sprites/link";

    _sens = Patate::DROITE;
    switch(_sens)
    {
        case Patate::DROITE:
            ddx = offset;
            spritePath.append("D");
            break;
        case Patate::GAUCHE:
            ddx = offset * -1.;
            spritePath.append("G");
            break;
        case Patate::HAUT:
            ddy = offset * -1.;
            spritePath.append("H");
            break;
        case Patate::BAS:
            ddy = offset;
            spritePath.append("B");
            break;
        default:
            spritePath.append("D");
            break;
    }

    if(cpt == 0)        // A droite
    {
        _imgCpt += 1;   // on incremente le cpteur de l'image affichee

        if(_imgCpt >= nbSprite) // si superieur on arrange
            _imgCpt = _imgCpt % nbSprite;

        qWarning() << spritePath.append(QString::number(_imgCpt + 1)) ;
        setPixmap(QPixmap(spritePath.append(QString::number(_imgCpt + 1))));
    }
    else
        if(cpt >= 3) // on remet a 0
            cpt = -1;   // car incremente apres

    moveBy(ddx, ddy);
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
