#include "ennemy.hpp"
#include "gamemanager.hpp"
#include "mouse.h"
#include<QDebug>

Ennemy::Ennemy(QGraphicsItem *parent):Personnage(parent)
{
    _sprites.append(":/images/patateSaiyen.png");

    _imgCpt = 0;
    _sens = Ennemy::DROITE;
    _gm = NULL;
    _touched = false;


    setPixmap(QPixmap(":/images/Sprites/linkD1.png"));
}

Ennemy::~Ennemy()
{
}

void Ennemy::advance(int step)
{
    static short cpt = 1, maxTour = 4, maxSprite = 4;
    const qreal maxX = 435, maxY = 354;
    QString spritePAth = ":/images/Sprites/link";
    qreal ddx = 0, ddy = 0, offset = 0.9;

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
        setPos(x(), maxY * -1.);
    else
    {
        if(y() < maxY * -1.)
            setPos(x(), maxY);
        else
        {
            if(x() > maxX)
                setPos(maxX * -1., y());
            else
                if(x() < maxX * -1.)
                    setPos(maxX, y());
        }
    }

    //qWarning() << "pos: " << x() << " - " << y();
    //GameManager.Instance()->setText(QString("pos: ").append(QString::number(x())).append(" - ").append(QString::number(y())));

    // test collision
    QList<QGraphicsItem*> listCollides = collidingItems();

    // si on touche qch
    if(listCollides.length() > 1) // le texte touche toujours
    {
        if(!_touched) // si on a pas deja gere le cas
            foreach(QGraphicsItem *item, listCollides)
            {
                // si c'est pas le texte
                if(item->type() != QGraphicsTextItem::Type)
                {
                    _touched = true;
                    doStrat();
                }
            }
    }
    else // sinon (si on touche rien)
        if(_touched)
            _touched = false;


    ++cpt; // compteur de tour
}

void Ennemy::doStrat()
{
    static short nusens = 0;

    if(_gm == NULL)
        _gm = GameManager::Instance();

    //_sens = (_sens + 2) % 4;


    while(1)
    {
        nusens = _gm->randInt(0, 3);

        if(nusens != _sens)
        {
            _sens = nusens;
            break;
        }
    }
}
