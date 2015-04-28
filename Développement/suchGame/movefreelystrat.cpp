#include <QDebug>
#include "movefreelystrat.hpp"
#include "ennemy.hpp"
#include "gamemanager.hpp"
#include "ball.hpp"
#include "barre.hpp"

MoveFreelyStrat::MoveFreelyStrat(Ennemy *parent) :
    _parent(parent)
{
}

MoveFreelyStrat::~MoveFreelyStrat()
{
    //qWarning() << "MoveFreelyStrat deleted.";
}

void MoveFreelyStrat::analyser ()
{
    ////qWarning() << "MoveFreelyStrat analysed.";
}

/**
 * @brief Verifie si le parent est touch et applique une strategie en consequence
 */
void MoveFreelyStrat::appliquer ()
{
    ////qWarning() << "MoveFreelyStrat applied.";

    // ------- test collision ------- //
    QList<QGraphicsItem*> listCollides = _parent->collidingItems();

    // si on touche qqch
    if(listCollides.length() > 1) // le texte touche toujours
    {
        if(!_parent->touched()) // si on a pas deja gere le cas
            foreach(QGraphicsItem *item, listCollides)
            {
                // si c'est pas le texte ni la barre de vie
                if(item->type() != QGraphicsTextItem::Type && item->type() != Barre::Type )
                {
                    _parent->setTouched(true);
                    /*
                    if(item->type() == Ball::Type)
                        doBallStrat((Ball*)item);
                    else
                    */
                    doStrat();
                }
            }
    }
    else // sinon (si on touche rien)
        if(_parent->touched())
            _parent->setTouched(false);
}

/**
 * @brief Donne un sens aléatoire au parent, different de son sens actuel
 */
void MoveFreelyStrat::doStrat()
{
    static short nusens = 0;
    static GameManager* const gm = GameManager::Instance();

    while(1)
    {
        nusens = gm->randInt(0, 3);

        if(nusens != _parent->getSens())
        {
            _parent->setSens(nusens);
            break;
        }
    }
}

// NOT USED
void MoveFreelyStrat::doBallStrat(Ball *item)
{
    _parent->loseHealth(item->getDegats());

}
