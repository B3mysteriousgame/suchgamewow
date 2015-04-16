#include "personnage.hpp"
#include "gamemanager.hpp"
#include <QDebug>
#include <QState>

Personnage::Personnage(QGraphicsItem* parent) :
    QObject(),
    QGraphicsPixmapItem(parent)
{
    //initStates();
}

void Personnage::initStates()
{
}

int Personnage::getSens() const
{
    return _sens;
}

void Personnage::setSens(const short sens)
{

    if(sens != 0 && sens != 1 && sens != 2 && sens != 3 && sens != -1 && sens != _sens)
    {
        /*qDebug() << "Erreur valeur sens.";
        throw;*/
    }
    else
       this->_sens = sens;
}

qreal Personnage::getPourcentageVie()
{
    qreal pourcentage;
    pourcentage = _actualhealth * 100 / _fullhealth;
    return pourcentage;
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

void Personnage::calculResistance()
{
    // TODO -> Récupérer résistance sur tout les items du personnage + Resistance de base ( Nécessite Item inventaire )
}

void Personnage::loseHealth(const int degats)
{
    int vraiDegats;

    vraiDegats = degats - _def;

    if(vraiDegats >= 1)
    {
        _actualhealth -= vraiDegats;

        if(_actualhealth < 0)
            _actualhealth = 0;

        qWarning() << "saucisse" << _actualhealth;
    }
}

QPointF Personnage::center() const
{
    qreal x, y;
    QRectF rec = boundingRect();

    x = rec.x() + rec.width() / 2;
    y = rec.y() + rec.height() / 2;

    return QPointF(x, y);
}

void Personnage::ChangeSensEtDeplacement(bool isPatate, int compteur, int maxTour, int maxSprite, QString path)
{
    qreal ddx = 0, ddy = 0, offset = 1;

    if(isPatate == false)
    {
       offset = 0.9;
    }
    switch (_sens)
    {
        case Personnage::DROITE:
            ddx += _speed * offset;
            path.append("D");
            break;
        case Personnage::GAUCHE:
            ddx += _speed * offset * -1.;
            path.append("G");
            break;
        case Personnage::BAS:
            ddy += _speed * offset;
            path.append("B");
            break;
        case Personnage::HAUT:
            ddy += _speed * offset * -1.;
            path.append("H");
            break;
        default:
            break;
    }

 /*   if(isPatate == true)
    {
        if(GameManager::Instance()->getPatate()->isMovin == false)
        {
            ddx = 0;
            ddy = 0;
            _imgCpt = 0; // incr apres
        }
    } */

    if(compteur >= maxTour) // on repasse a 0
        compteur = 0; // incremente apres donc = 1 la prochaine fois
    else
        if(compteur == 1) // on change l'image
        {
            _imgCpt += 1;

            if(_imgCpt > maxSprite)
                _imgCpt = 1;

            path.append(QString::number(_imgCpt));
            setPixmap(QPixmap(path));
        }

    moveBy(ddx, ddy);
}
