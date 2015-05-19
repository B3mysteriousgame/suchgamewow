#include "personnage.hpp"
#include "gamemanager.hpp"
#include "patate.hpp"
#include "highlighteffect.hpp"
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

    //setGraphicsEffect(new HighlightEffect(0.3, this));
    setGraphicsEffect(new QGraphicsOpacityEffect(this));
    graphicsEffect()->setEnabled(false);

    initAnim();

    connect(_timerTargetable, SIGNAL(timeout()), this, SLOT(setTargetable()));
}

bool Personnage::operator!=(const Personnage &p) const
{
    return !(*this == p);
}

bool Personnage::operator==(const Personnage &p) const
{
    if( this->_targetable == p.isTargetable()
            && this->_fullhealth == p.getFullHealth()
            && this->_actualhealth == p.getActualHealth()
            && this->_atk == p.getAtk()
            && this->_def == p.getDef()
            && this->_mana == p.getMana()
            && this->_lvl == p.getLvl()
            && this->_sens == p.getSens()
            && this->_speed == p.getSpeed()
            && this->_movin == p.isMovin())
        return true;

    return false;
}

Personnage::~Personnage()
{
    if(_sm != NULL)
        delete(_sm);

    delete(_timerTargetable);
}

void Personnage::setTargetable(bool targetable)
{
    if(targetable == false) // was targetable, now isn't
        _timerTargetable->start(_timout);
    else // wasn't targetable, now is
        _timerTargetable->stop();

    _targetable = targetable;
    this->graphicsEffect()->setEnabled(!targetable);
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


            if(_actualhealth == 0)
                emit deadPerso();

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

void Personnage::ChangeSensEtDeplacement()
{
    qreal ddx = 0, ddy = 0, offset = 0.9;

    if(this->type() == Patate::Type)
        offset = 1.1;

    switch (_sens)
    {
        case Personnage::DROITE:
            ddx += _speed * offset;
            break;
        case Personnage::GAUCHE:
            ddx += _speed * offset * -1.;
            break;
        case Personnage::BAS:
            ddy += _speed * offset;
            break;
        case Personnage::HAUT:
            ddy += _speed * offset * -1.;
            break;
        default:
            break;
    }

    moveBy(ddx, ddy);
}

void Personnage::MoveToDest(QPointF pointDest)
{
    int dplct_x = abs(pointDest.x() - this->x());
    int dplct_y = abs(pointDest.y() - this->y());

if( abs(dplct_x - dplct_y) > 5 )
{
    if(dplct_x > dplct_y ){ // Choix deplacement X ou Y en premier
        if(pointDest.x() - this->x() > 0) // Choix sens selon negatif ou positif
        {
            _sens = Personnage::DROITE;
        }
        else
        {
            _sens = Personnage::GAUCHE;
        }
    }
    else //idem
    {
        if((pointDest.y() - this->y()) > 0)
        {
            _sens = Personnage::BAS;
        }
        else
        {
            _sens = Personnage::HAUT;
        }
    }
    ChangeSensEtDeplacement();
   }
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


