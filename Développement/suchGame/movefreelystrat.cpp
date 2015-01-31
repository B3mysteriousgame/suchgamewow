#include <QDebug>
#include "movefreelystrat.hpp"
#include "ennemy.hpp"
#include "gamemanager.hpp"

MoveFreelyStrat::MoveFreelyStrat(Ennemy *parent) :
    _parent(parent)
{
}

MoveFreelyStrat::~MoveFreelyStrat()
{
    qWarning() << "MoveFreelyStrat deleted.";
}

void MoveFreelyStrat::analyser ()
{
    //qWarning() << "MoveFreelyStrat analysed.";
}

void MoveFreelyStrat::appliquer ()
{
    //qWarning() << "MoveFreelyStrat applied.";

    // ------- test collision ------- //
    QList<QGraphicsItem*> listCollides = _parent->collidingItems();

    // si on touche qch
    if(listCollides.length() > 1) // le texte touche toujours
    {
        if(!_parent->touched()) // si on a pas deja gere le cas
            foreach(QGraphicsItem *item, listCollides)
            {
                // si c'est pas le texte
                if(item->type() != QGraphicsTextItem::Type)
                {
                    _parent->setTouched(true);
                    doStrat();
                }
            }
    }
    else // sinon (si on touche rien)
        if(_parent->touched())
            _parent->setTouched(false);
}

void MoveFreelyStrat::doStrat()
{
    static short nusens = 0;
    static GameManager *gm = GameManager::Instance();

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
