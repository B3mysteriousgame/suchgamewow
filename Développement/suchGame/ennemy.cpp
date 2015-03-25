#include "ennemy.hpp"
#include "gamemanager.hpp"
#include "mouse.h"
#include "movefreelystrat.hpp"
#include<QDebug>
#include "barre.hpp"

Ennemy::Ennemy(QGraphicsItem *parent) :
    Personnage(parent)
{
    _sprites.append(":/images/patateSaiyen.png");
    _imgCpt = 0;
    _sens = Ennemy::DROITE;
    _gm = NULL;
    _touched = false;
    _strat = new MoveFreelyStrat(this);
    _xpDon = 70;
    _fullhealth = 100;
    _actualhealth = _fullhealth;
    _def = 25;
    setPixmap(QPixmap(":/images/Sprites/linkD1.png"));

    _barre = new Barre();
    _barre->moveBy(-12,-15);
    _barre->setParentItem(this);
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
}


void Ennemy::advance(int)
{
    // const pointer to GameManager
    static GameManager* const Michel = GameManager::Instance();
    static short cpt = 1, maxTour = 4, maxSprite = 4, changeSensChance = 100, newsens = -1;
    /*
    static const qreal maxX = Michel->getView()->width();
    static const qreal maxY = Michel->getView()->height();
    */

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

    handleSceneBounder();

    //qWarning() << "pos: " << x() << " - " << y();
    //GameManager.Instance()->setText(QString("pos: ").append(QString::number(x())).append(" - ").append(QString::number(y())));

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
