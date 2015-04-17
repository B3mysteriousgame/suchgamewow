#include "barre.hpp"

Barre::Barre(bool estPatate) :
    QGraphicsItem()
{
     _color = (Qt::red);
     _largeur = 50;
     _hauteur = 5;
     _largeurInit = _largeur;
     _hauteurInit = _hauteur;

     if(estPatate == true)
     {
         _largeur = 5;
         _hauteur = 50;
         _largeurInit = _largeur;
         _hauteurInit = _hauteur;

     }
}

Barre::~Barre()
{

}

void Barre::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    //painter->setBrush(Qt::black); Plus jolie avec la transparence
    painter->drawRect(0,0,_largeurInit + 2,_hauteurInit + 2);

    painter->setBrush(_color);
    painter->drawRect(1,1,_largeur,_hauteur);  // (Posx,Posy,largeur,hauteur)

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

void Barre::setLargeur(qreal largeur)
{
    _largeur = largeur;
}

qreal Barre::getLargeur()
{
    return _largeur;
}

void Barre::setHauteur(qreal hauteur)
{
    _hauteur = hauteur;
}

qreal Barre::getHauteur()
{
    return _hauteur;
}
