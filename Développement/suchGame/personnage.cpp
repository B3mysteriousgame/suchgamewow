#include "personnage.hpp"
#include "gamemanager.hpp"
#include <QDebug>

int Personnage::getSens() const
{
    return _sens;
}

void Personnage::setSens(const short sens)
{

    if(sens != 0 && sens != 1 && sens != 2 && sens != 3 )
    {
        qDebug() << "Erreur valeur sens.";
        throw;
    }
    else
       this->_sens = sens;
}

qreal Personnage::getSpeed() const
{
    return _speed;
}

void Personnage::setSpeed(const qreal val)
{
    _speed = val;
}

int Personnage::getFullHealth() const
{
    return _fullhealth;
}

void Personnage::setFullHealth(const int health)
{
    _fullhealth = health;
}

int Personnage::getActualHealth() const
{
    return _actualhealth;
}

void Personnage::setActualHealth(const int health)
{
    _actualhealth = health;
}

void Personnage::loseHealth(const int degats)
{
    _actualhealth -= degats;
    qWarning() << "saucisse" << _actualhealth;
    if(_actualhealth <= 0)
        _actualhealth = 0;
}

QPointF Personnage::center() const
{
    qreal x, y;
    QRectF rec = boundingRect();

    x = rec.x() + rec.width() / 2;
    y = rec.y() + rec.height() / 2;

    return QPointF(x, y);
}
