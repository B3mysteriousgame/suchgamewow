#include "ennemy.hpp"
#include "gamemanager.hpp"
#include "mouse.h"
#include "movefreelystrat.hpp"
#include "strat1.hpp"
#include<QDebug>
#include "barre.hpp"
#include <QList>

Ennemy::Ennemy(int lvl, QGraphicsItem *parent) :
    Personnage(parent)
{
    //_sprites.append(":/images/patateSaiyen.png");
    _imgCpt = 0;
    _sens = Ennemy::DROITE;
    _gm = NULL;
    _touched = false;
    _strat = new MoveFreelyStrat(this);
    _lvl = lvl;
    _xpDon = 20 + (9 * (_lvl - 1));
    _fullhealth = 500 + (12 * (_lvl - 1));
    _actualhealth = _fullhealth;
    _atk = 80 + (15 * (_lvl - 1));
    _def = 30 + (11 * (_lvl - 1));
    _speed = 1;
    setPixmap(QPixmap(":alex/images/Sprites/alex/alexD1.png"));

    _barre = new Barre(false);
    _barre->moveBy(-12,-15);
    _barre->setParentItem(this);

    _patateproche = false;
    _movin = true;

    _targetable = true;
    _sm = new SpriteManager(this, "alex", 4);
}

int Ennemy::getXpDon() const
{
    return _xpDon;
}

Ennemy::~Ennemy()
{
    delete(_strat);
    delete(_barre);
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

    QString spritePAth = ":alex/images/Sprites/alex/alex";
    static short cpt = 1, maxTour = 4, maxSprite = 4, changeSensChance = 100, newsens = -1;

    handleSceneBounder();

    if(_patateproche == true)
    {
        _strat = new Strat1(this);
      // Calcul nouvel coordonées à parcourir pour rejoindre la patate
      int dplct_x = abs(pointpatate.x() - this->x());
      int dplct_y = abs(pointpatate.y() - this->y());

      if(dplct_x > dplct_y){ // Choix deplacement X ou Y en premier
          if(pointpatate.x() - this->x() > 0) // Choix sens selon negatif ou positif
          {
              _sens = Ennemy::DROITE;
          }
          else
          {
              _sens = Ennemy::GAUCHE;
          }
      }
      else //idem
      {
          if((pointpatate.y() - this->y()) > 0)
          {
              _sens = Ennemy::BAS;
          }
          else
          {
              _sens = Ennemy::HAUT;
          }
      }

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

    ChangeSensEtDeplacement(cpt,maxTour,maxSprite,spritePAth);

    if(cpt >= maxTour) // on repasse a 0
        cpt = 0; // incremente apres donc = 1 la prochaine fois

    // exécute la strat
    _strat->executer();

    ++cpt; // compteur de tour
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
