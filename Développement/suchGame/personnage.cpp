#include "personnage.hpp"
#include "gamemanager.hpp"
#include "patate.hpp"
#include <QDebug>
#include <QState>

Personnage::Personnage(QGraphicsItem* parent) :
    QObject(),
    QGraphicsPixmapItem(parent)
{
    //initStates();
    _sm = NULL;
    _targetable = true;
    _timerTargetable = new QTimer();
    _timout = 100;
    initAnim();

    connect(_timerTargetable, SIGNAL(timeout()), this, SLOT(setTargetable()));
}

Personnage::~Personnage()
{
    if(_sm != NULL)
        delete(_sm);

    delete(_timerTargetable);

    if(_animation != NULL)
        delete(_animation);
}

void Personnage::setTargetable(bool targetable)
{
    if(targetable == false) // was targetable
        _timerTargetable->start(_timout);
    else // wasn't targetable
        _timerTargetable->stop();

    _targetable = targetable;
}

void Personnage::setVisible(bool vis)
{
    qWarning() << "VISIBLE CHANGED";
    QGraphicsPixmapItem::setVisible(vis);
}

void Personnage::initAnim()
{/*
    _anim.setParent(this);
    _anim.setDuration(1000);
    _anim.setPropertyName(QByteArray("visible"));

    _anim.setStartValue(QRect(0, 0, 100, 30));
    _anim.setEndValue(QRect(250, 250, 100, 30));


    _anim.start();
*/}

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

    if(_sm != NULL)
    {
        if(sens != sens)
            _sm->razCpt();
    }
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

    if(this->isTargetable())
    {
        vraiDegats = degats - _def;

        if(vraiDegats >= 1)
        {
            _actualhealth -= vraiDegats;

            if(_actualhealth < 0)
                _actualhealth = 0;

            //  qWarning() << "saucisse" << _actualhealth;
        }
        this->setTargetable(false);
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

void Personnage::ChangeSensEtDeplacement(int compteur, int maxTour, int maxSprite, QString path)
{
    qreal ddx = 0, ddy = 0, offset = 1;

    if(this->type() == Patate::Type)
        offset = 0.9;

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

    if(compteur >= maxTour) // on repasse a 0
        compteur = 0; // incremente apres donc = 1 la prochaine fois
    else
        if(compteur == 1) // on change l'image
        {
            _imgCpt += 1;

            if(_imgCpt > maxSprite)
                _imgCpt = 1;

            path.append(QString::number(_imgCpt));

            /*
            if(this->type() != Patate::Type) // si pas une patate
                setPixmap(QPixmap(path));
            */
        }

    moveBy(ddx, ddy);
}

QString Personnage::getStrSens() const
{
    QString sens;
    switch (_sens)
    {
        case Personnage::BAS:
            sens = "Bas";
            break;
        case Personnage::GAUCHE:
            sens = "Gauche";
            break;
        case Personnage::HAUT:
            sens = "Haut";
            break;
        case Personnage::DROITE:
            sens = "Droite";
            break;
        default:
            break;
    }
    return sens;
}

bool Personnage::isMovin() const
{
    return _movin;
}

void Personnage::setMovin(const bool move)
{
    _movin = move;

    if(_sm != NULL)
    {
        /*
        if(move)
        {
            if(!_sm->isRunning())
                _sm->start();
        }
        else
        {
            if(_sm->isRunning())
                _sm->stop();
        }
        */
        //emit moveChanged();
    }
}

bool Personnage::operator==(const Personnage &p) const
{
    if(this->_actualhealth != p.getActualHealth()
            || this->_atk != p.getAtk()
            || this->_fullhealth != p.getFullHealth()
            || this->_movin != p.isMovin()
            || this->_sens != p.getSens()
            || this->_speed != p.getSpeed()
            || this->type() != p.type())
        return false;
    else
        return true;
}

bool Personnage::operator!=(const Personnage &p) const
{
    return !(*this == p);
}
