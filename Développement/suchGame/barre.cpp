#include "barre.hpp"

Barre::Barre() :
    QGraphicsItem()
{
     _color = (Qt::red);
     _largeur = 50;
}

Barre::~Barre()
{

}

void Barre::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    painter->setBrush(Qt::black);
    painter->drawRect(0,0,52,7);

    painter->setBrush(_color);
    painter->drawRect(1,1,_largeur,5);  // (Posx,Posy,largeur,hauteur)

}

void Barre::setColor(QColor color){
    _color = color;
}

QColor Barre::getColor() const {
    return(_color);
}

QRectF Barre::boundingRect() const
{
    QRectF rect = QRectF(0,0,52,7);

    return rect;
}

