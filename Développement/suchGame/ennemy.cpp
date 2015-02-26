#include "ennemy.hpp"
#include "gamemanager.hpp"
#include "mouse.h"
#include "movefreelystrat.hpp"
#include<QDebug>

Ennemy::Ennemy(QGraphicsItem *parent) :
    Personnage(parent)
{
    _sprites.append(":/images/patateSaiyen.png");

    _imgCpt = 0;
    _sens = Ennemy::DROITE;
    _gm = NULL;
    _touched = false;
    _strat = new MoveFreelyStrat(this);
    _fullhealth = 100;
    _actualhealth = _fullhealth;
    _resistance = 25;
    setPixmap(QPixmap(":/images/Sprites/linkD1.png"));
}

Ennemy::~Ennemy()
{
    delete(_strat);
}


void Ennemy::advance(int step)
{
    static GameManager *Michel = GameManager::Instance();
    static short cpt = 1, maxTour = 4, maxSprite = 4, changeSensChance = 100, newsens = -1;
    static const qreal maxX = Michel->getView()->width();
    static const qreal maxY = Michel->getView()->height();

    QString spritePAth = ":/images/Sprites/link";
    qreal ddx = 0, ddy = 0, offset = 0.9;


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

    //_sens = Patate::BAS;
    switch (_sens)
    {
        case Ennemy::DROITE:
            ddx += offset;
            spritePAth.append("D");
            break;
        case Ennemy::GAUCHE:
            ddx += offset * -1.;
            spritePAth.append("G");
            break;
        case Ennemy::BAS:
            ddy += offset;
            spritePAth.append("B");
            break;
        case Ennemy::HAUT:
            ddy += offset * -1.;
            spritePAth.append("H");
            break;
        default:
            break;
    }

    if(cpt >= maxTour) // on repasse a 0
        cpt = 0; // incremente apres donc = 1 la prochaine fois
    else
        if(cpt == 1) // on change l'image
        {
            _imgCpt += 1;

            if(_imgCpt > maxSprite)
                _imgCpt = 1;

            spritePAth.append(QString::number(_imgCpt));
            setPixmap(QPixmap(spritePAth));
        }

    moveBy(ddx, ddy);

    if(y() > maxY)
        setPos(x(), 0);
    else
    {
        if(y() < 0)
            setPos(x(), maxY);
        else
        {
            if(x() > maxX)
                setPos(0, y());
            else
                if(x() < 0)
                    setPos(maxX, y());
        }
    }

    //qWarning() << "pos: " << x() << " - " << y();
    //GameManager.Instance()->setText(QString("pos: ").append(QString::number(x())).append(" - ").append(QString::number(y())));

    // test collision
    _strat->executer();

    ++cpt; // compteur de tour
}

