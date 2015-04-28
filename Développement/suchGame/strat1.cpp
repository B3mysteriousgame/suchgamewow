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

    // si on touche qqch
    if(listCollides.length() > 0) // le texte touche toujours
    {
        if(!_parent->touched()) // si on a pas deja gere le cas
            foreach(QGraphicsItem *item, listCollides)
            {
                switch (item->type())
                {
                    case QGraphicsTextItem::Type:
                        _parent->setTouched(false);

                    case Barre::Type:
                        _parent->setTouched(false);

                    case Ennemy::Type: // test déplacer ennemy en contact avec ennemy ( Fonctionne tant qu'il n'entre pas en collision avec patate )
                        _parent->setTouched(true);
                        _parent->moveBy(GameManager::Instance()->randInt(3,20),GameManager::Instance()->randInt(3,20));

                    case Patate::Type:
                        _parent->setTouched(true);
                        GameManager::Instance()->getPatate()->loseHealth(51);
                        //qWarning() << "Strat1 analysed.---" << GameManager::Instance()->getPatate()->getActualHealth();

                }
            }
    }
    else // sinon (si on touche rien)
        if(_parent->touched())
            _parent->setTouched(false);


}
