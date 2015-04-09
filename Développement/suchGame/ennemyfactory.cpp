#include "ennemyfactory.h"
#include "barre.hpp"
#include <math.h>
#include "angleoperation.hpp"
#include "gamemanager.hpp"
#include <QtDebug>

EnnemyFactory::EnnemyFactory()
{


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
    barre->moveBy(-4,0);
    barre->setParentItem(ennemy);

    GameManager::Instance()->addItemToScene(ennemy);

    _listeMichels.append(ennemy);

    if( _listeMichels.length() == 10)
    {
        if(GameManager::Instance()->isTimerActive())
            GameManager::Instance()->stopTimer();
    }
    else
        GameManager::Instance()->startTimer(100 * (GameManager::Instance()->randInt(1,50)));

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

void EnnemyFactory::removeEnnemy(Ennemy *it)
{
    _listeMichels.removeOne(it);
    qWarning() <<"nbmichel_indaListe :" <<  _listeMichels.length() ;
}
