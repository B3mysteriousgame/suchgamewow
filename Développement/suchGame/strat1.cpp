#include <QDebug>
#include "strat1.hpp"
#include "gamemanager.hpp"
#include "patate.hpp"
#include "barre.hpp"

Strat1::Strat1(Ennemy *parent) :
      _parent(parent)
{
    // Utilisation de cette strat pour lancer l'attaque lorsque les ennemis sont proche de la patate

}

Strat1::~Strat1()
{
    //qWarning() << "Strat1 deleted.";
}

void Strat1::analyser ()
{
    ////qWarning() << "Strat1 analysed.";
}

void Strat1::appliquer ()
{
    QList<QGraphicsItem*> listCollides = _parent->collidingItems();
    QList<QGraphicsItem*> ennemyCollided;
    QPointF dest;
    static GameManager* const jose = GameManager::Instance();
    static Patate* const michel = jose->getPatate();

    // si on touche qqch
    if(listCollides.length() > 0)
    {
        foreach(QGraphicsItem *item, listCollides)
        {
            if(item->type() == Ennemy::Type)
               {
                 ennemyCollided.append(item);
               }
        }
    }
    if(ennemyCollided.length() > 0)
    {
       if(!_parent->touched()) // si on a pas deja gere le cas
       {
            foreach(QGraphicsItem *item, ennemyCollided)
            {
                Ennemy* michel = (Ennemy*)item;
                _parent->setTouched(true);
                int sens = michel->getSens();
                switch(sens)
                {
                    case Ennemy::BAS:
                        dest = QPointF(michel->x(),michel->y() + (10*_parent->getSpeed()));

                    case Ennemy::HAUT:
                        dest = QPointF(michel->x(),michel->y() + (-10*_parent->getSpeed()));

                    case Ennemy::DROITE:
                        dest = QPointF(michel->x() + (-10*_parent->getSpeed()),michel->y());

                    case Ennemy::GAUCHE:
                        dest = QPointF(michel->x() + (10*_parent->getSpeed()),michel->y());
                }
            }
       }
       else // sinon (si on touche rien)
       {
           if(_parent->touched())
               _parent->setTouched(false);
       }

       _parent->MoveToDest(dest);
    }
}

