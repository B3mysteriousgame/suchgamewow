#include "ennemy.hpp"
#include "gamemanager.hpp"
#include "mouse.h"
#include "movefreelystrat.hpp"
#include "strat1.hpp"
#include "strat2.hpp"
#include<QDebug>
#include "barre.hpp"
#include <QList>

Ennemy::Ennemy(short lvl, QGraphicsItem *parent) :
    Personnage(parent)
{
    _imgCpt = 0;
    _sens = Ennemy::DROITE;
    _gm = NULL;

    _touched = false;
    _strat = new MoveFreelyStrat(this);

//    _fullhealth = vie;
//    _actualhealth = vie;
//    _lvl= lvl;
//    _xpDon = (30 + (9 * (_lvl - 1))) * 1.3;
//    _atk = 80 + (15 * (_lvl - 1));
//    _def = 30 + (11 * (_lvl - 1));
    setLevel(lvl);


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
}

Ennemy::Ennemy(QGraphicsItem *parent) :
    Personnage(parent)
{
    _imgCpt = 0;
    _sens = Ennemy::DROITE;
    _gm = NULL;
    _touched = false;
    _strat = new MoveFreelyStrat(this);
    setLevel(1);

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
}

void Ennemy::setTargetable(bool targetable)
{
    /* Pour l'animation, semnle fonctionner
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
    */

    Personnage::setTargetable(targetable);
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

Barre *Ennemy::getBarre() const
{
    return _barre;
}

void Ennemy::loseHealth(int degats)
{
    qreal pourcentage;
    Personnage::loseHealth(degats); // personnage test si targetable

    pourcentage = getPourcentageVie();
    _barre->setLargeur(pourcentage);
}


void Ennemy::advance(int)
{
    static GameManager* const Michel = GameManager::Instance();
    static short changeSensChance = 100, newsens = -1;

    QPointF pointpatate = Michel->getPatatePos();
    QPointF pointennemy = QPointF (this->pos().x(),this->pos().y());
    QLineF ligne = QLineF(pointpatate,pointennemy);


    handleSceneBounder();
    hidePointAggro();

    if(_patateproche == true)
    {
      _strat = new Strat1(this);
      showPointAggro();

      if(ligne.length() > 200)
      {
          _patateproche = false;
      }
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

/**
 * @brief Ennemy::handleSceneBounder
 *  Move Ennemy to the opposite side of the map if it
 * crosses map's bounderies
 */
void Ennemy::handleSceneBounder()
{
    static const QRectF bounder = GameManager::Instance()->getScene()->sceneRect();
    qreal newx = x(), newy = y();


    if(y() > bounder.bottomLeft().y())
        newy = bounder.topLeft().y();
    else
    {
        if(y() < bounder.topLeft().y())
            newy = bounder.bottomLeft().y();
        else
        {
            if(x() > bounder.topRight().x())
                newx = bounder.topLeft().x();
            else
                if(x() < bounder.topLeft().x())
                    newx = bounder.topRight().x();
        }
    }

    setPos(newx, newy);
}

void Ennemy::hidePointAggro()
{
    _pointAggro->hide();
    _pointAggro->setActive(false);
}

void Ennemy::showPointAggro()
{
    _pointAggro->setActive(true);
    _pointAggro->show();
}

void Ennemy::setLevel(const int lvl)
{
    _lvl = lvl;
    _xpDon = (30 + (9 * (_lvl - 1))) * 1.4;
    _fullhealth = 500 + (12 * (_lvl - 1));
    _actualhealth = _fullhealth;
    _atk = 80 + (15 * (_lvl - 1));
    _def = 30 + (11 * (_lvl - 1));
}
