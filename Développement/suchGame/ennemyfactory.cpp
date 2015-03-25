#include "ennemyfactory.h"
#include "barre.hpp"
#include <math.h>
#include "angleoperation.hpp"
#include "gamemanager.hpp"

EnnemyFactory::EnnemyFactory()
{
    _gm = GameManager::Instance();
    _timerPopEnnemy = _gm->getPopTimer();
}

EnnemyFactory::~EnnemyFactory()
{

}

void EnnemyFactory::createEnnemy()
{
    Ennemy *ennemy = new Ennemy();
    ennemy->setPos(::sin((1 * 6.28) / 7) * 200,
                   ::cos((1 * 6.28) / 7) * 200);
    Barre *barre = ennemy->getBarre();
    barre->moveBy(-12,-15);
    barre->setParentItem(ennemy);
    _gm->addItemToScene(ennemy);

    _listeMichels.append(ennemy);

    if( _listeMichels.length() == 10) // le max
      {
        if(_timerPopEnnemy->isActive())
            _timerPopEnnemy->stop();
      }
    else
        _timerPopEnnemy->start( 100 * (_gm->randInt(1,50)) );

}


/**
 * @brief Retourne l'objet ennemy de la liste listeMichel en fonction de listpos
 * @param listpos position de l'ennemy dans la liste
 * @return l'objet ennemy
 */
Ennemy EnnemyFactory::getEnnemyAt(int listpos)
{
    return _listeMichels.at(listpos);
}

int EnnemyFactory::getNbEnnemy()
{
    return _listeMichels.length();
}

