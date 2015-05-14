#include "barre.hpp"
#include <QGraphicsEffect>

Barre::Barre(bool estPatate) :
    QObject(),
    QGraphicsItem()
{
     _color = QColor(Qt::red);
     _bkColor =  QColor(255, 255, 0, 0);
     _largeur = 50;
     _hauteur = 5;
     _largeurInit = _largeur;
     _hauteurInit = _hauteur;



     if(estPatate == true)
     {/*
         _largeur = 5;
         _hauteur = 50;
         _largeurInit = _largeur;
         _hauteurInit = _hauteur;

     */}

     QObject::connect(&_effectTimer, SIGNAL(timeout()), this, SLOT(stopEffect()));
}

Barre::~Barre()
{

}

/**
 * @brief Barre::stopEffect Sets the effect to not enabled.
 *  Called by _effectTimer timeout()
 */
void Barre::stopEffect()
{
    _bkColor.setAlpha(0);
    update();
}

void Barre::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(_bkColor); //Plus jolie avec la transparence
    painter->drawRect(0, 0, _largeurInit + 2, _hauteurInit + 2);

    painter->setBrush(_color);
    painter->drawRect(1, 1, _largeur, _hauteurInit);  // (Posx,Posy,largeur,hauteur)

}

void Barre::setColor(QColor color){
    _color = color;
}

QColor Barre::getColor() const {
    return _color;
}

QRectF Barre::boundingRect() const
{
    QRectF rect = QRectF(0,0,52,7);

    return rect;
}

void Barre::setLargeur(qreal plargeur)
{
    // plargeur est un pourcentage donc
    int largeur = plargeur * _largeurInit / 100;

    if(largeur > _largeurInit)
        _largeur = _largeurInit;
    else
    {
        if(largeur < 0)
            _largeur = 0;
        else
            _largeur = largeur;
    }

    _bkColor.setAlpha(128);
    _effectTimer.start(200);
}

qreal Barre::getLargeur()
{
    return _largeur;
}

void Barre::setHauteur(qreal hauteur)
{
    if(hauteur > _hauteurInit)
        _hauteur = _hauteurInit;
    else
    {
        if(hauteur < 0)
            _hauteur = 0;
        else
            _hauteur = hauteur;
    }
}

qreal Barre::getHauteur()
{
    return _hauteur;
}
