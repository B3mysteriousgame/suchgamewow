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
    static GameManager* const jose = GameManager::Instance();
    static Patate* const michel = jose->getPatate();

    // si on touche qqch
    if(listCollides.length() > 0)
    {
        if(!_parent->touched()) // si on a pas deja gere le cas
            foreach(QGraphicsItem *item, listCollides)
            {
                switch (item->type())
                {
                    case QGraphicsTextItem::Type:
                        _parent->setTouched(false);
                        break;

                    case Barre::Type:
                        _parent->setTouched(false);
                        break;

                    case Ennemy::Type: // test déplacer ennemy en contact avec ennemy ( Fonctionne tant qu'il n'entre pas en collision avec patate )
                        _parent->setTouched(true);
                        _parent->moveBy(jose->randInt(3,20),jose->randInt(3,20));
                        break;

                    case Patate::Type:
                        _parent->setTouched(true);
                        michel->loseHealth( _parent->getAtk() );
                        //qWarning() << "Strat1 analysed.---" << jose->getPatate()->getActualHealth();
                        break;

                }
            }
        else // si on a deja gere le cas
        {
            // oncheck si on collide avec la patate
            if(_parent->collidesWithItem(michel)) // probablement lourd...
            {
                // on la marave !
                michel->loseHealth( _parent->getAtk() );
            }
        }
    }
    else // sinon (si on touche rien)
        if(_parent->touched())
            _parent->setTouched(false);


}
