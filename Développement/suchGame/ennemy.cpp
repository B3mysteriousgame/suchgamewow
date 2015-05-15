#include "ennemy.hpp"
#include "gamemanager.hpp"
#include "mouse.h"
#include "movefreelystrat.hpp"
#include "strat1.hpp"
#include "strat2.hpp"
#include<QDebug>
#include "barre.hpp"
#include <QList>

Ennemy::Ennemy(QGraphicsItem *parent) :
    Personnage(parent)
{
    //_sprites.append(":/images/patateSaiyen.png");
    _imgCpt = 0;
    _sens = Ennemy::DROITE;
    _gm = NULL;
    _touched = false;
    _strat = new MoveFreelyStrat(this);
    _lvl = 1;
    _xpDon = 20 + (9 * (_lvl - 1));
    _fullhealth = 500 + (12 * (_lvl - 1));
    _actualhealth = _fullhealth;
    _atk = 80 + (15 * (_lvl - 1));
    _def = 30 + (11 * (_lvl - 1));
    _speed = 1;
    setPixmap(QPixmap(":alex/images/Sprites/alex/alexD1.png"));

    _pointAggro = new QGraphicsPixmapItem(QPixmap(":/images/Sprites/pointAggro.png"));
    _pointAggro->setParentItem(this);
    _pointAggro->setActive(true);

    _barre = new Barre(false);
    _barre->moveBy(-12,-15);
    _barre->setParentItem(this);

    _patateproche = false;
    _movin = true;

    _targetable = true;
    _sm = new SpriteManager(this, "alex", 4);

    initAnimation();
}

void Ennemy::setTargetable(bool targetable)
{
    if(_animation != NULL)
    {
        if(targetable == false) // was targetable
        {
            qWarning() << "anim started";
            _animation->start();
        }
        else                    // was not targetable
        {
            //qWarning() << "anim stopped";
            //_animation->stop();
        }
    }

    Personnage::setTargetable(targetable);
}

void Ennemy::initAnimation()
{
    _animation = new QPropertyAnimation(this, "visible");
    _animation->setDuration(500);
    _animation->setStartValue(true);
    _animation->setEndValue(false);
    _animation->setLoopCount(-1); // endless loop biatch
}

int Ennemy::getXpDon() const
{
    return _xpDon;
}

Ennemy::~Ennemy()
{
    delete(_strat);
    delete(_barre);
    delete(_pointAggro);
}

Barre *Ennemy::getBarre()
{
    return _barre;
}

void Ennemy::loseHealth(int degats)
{
    qreal pourcentage;
    Personnage::loseHealth(degats);
    pourcentage = Ennemy::getPourcentageVie();
    _barre->setLargeur(pourcentage/2);
    qWarning() << "jose chibre bonchour" << this->_actualhealth;
}


void Ennemy::advance(int)
{
    static GameManager* const Michel = GameManager::Instance();
    QPointF pointpatate = Michel->getPatatePos();
    QPointF pointennemy = QPointF (this->pos().x(),this->pos().y());
    QLineF ligne = QLineF(pointpatate,pointennemy);

    static short changeSensChance = 100, newsens = -1;

    handleSceneBounder();

    hidePointAggro();

    if(_patateproche == true)
    {
        _strat = new Strat1(this);
      // Calcul nouvel coordonées à parcourir pour rejoindre la patate

      MoveToDest(pointpatate);

      showPointAggro();

      if(ligne.length() > 200)
      {
          _patateproche = false;
      }
     /* if(ligne.length() < 3) // 3 à remplacer par portée attaque
      {
          /* static QPointF pointcloche = new QPointF(0,0);
          _strat = new Strat2(this,pointcloche);
      }*/

    }
    else
    {
        // ---- Changement de sens aleatoire ----
         //1 chance sur changeSensChance de changer de sens
        if(Michel->randInt(1,changeSensChance)==1)
            while(1)
            {
                newsens = Michel->randInt(0, 3);
                if(newsens != _sens)
                {
                    _sens = newsens;
                    break;
                }
            }
        if(ligne.length() < 200)
        {
            _patateproche = true;
        }
        _strat = new MoveFreelyStrat(this);
    }

    ChangeSensEtDeplacement();
    _strat->executer();
}

void Ennemy::handleSceneBounder()
{
    static const QRectF bounder = GameManager::Instance()->getScene()->sceneRect();

    if(y() > bounder.bottomLeft().y())
        setPos(x(), bounder.topLeft().y());
    else
    {
        if(y() < bounder.topLeft().y())
            setPos(x(), bounder.bottomLeft().y());
        else
        {
            if(x() > bounder.topRight().x())
                setPos(bounder.topLeft().x(), y());
            else
                if(x() < bounder.topLeft().x())
                    setPos(bounder.topRight().x(), y());
        }
    }
}

void Ennemy::hidePointAggro()
{
    //_timerPointAggro->stop();
    _pointAggro->hide();
    _pointAggro->setActive(false);
}

void Ennemy::showPointAggro()
{
    if (!_pointAggro->isActive())
          _pointAggro->setActive(true);

    _pointAggro->show();
}

void Ennemy::setLevel(int lvl)
{
    _lvl = lvl;
}
