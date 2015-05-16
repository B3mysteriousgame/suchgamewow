#include "ennemyfactory.h"
#include "barre.hpp"
#include <math.h>
#include "angleoperation.hpp"
#include "gamemanager.hpp"
#include "patate.hpp"
#include <QtDebug>
#include <ennemylopette.h>

EnnemyFactory::EnnemyFactory()
{


}

EnnemyFactory::~EnnemyFactory()
{

}

void EnnemyFactory::createEnnemy()
{
    static const float diff = 0.1;
    static GameManager* const gm = GameManager::Instance();

    int diffNiv = (gm->getPatate())->getLvl();
    short plusOuMoins = gm->randInt(1,2);

    switch (plusOuMoins)
    {
        case 1:
            diffNiv += diffNiv * diff;
            break;
        default:
            diffNiv -= diffNiv * diff;
            break;
    }

    if(diffNiv == 0)
        diffNiv = 1;

    if(gm->randInt(1,6) == 1)
    {
       EnnemyLopette *ennemyl = new EnnemyLopette();
       ennemyl->setLevel(diffNiv);
       qWarning() << "An ennemylopette popped lvl" << diffNiv;

       ennemyl->setPos(::sin((1 * 6.28) / 7) * 200,
                      ::cos((1 * 6.28) / 7) * 200);


       gm->addItemToScene(ennemyl);

       _listeMichels.append(ennemyl);

       if( _listeMichels.length() == EnnemyFactory::MAXENN)
       {
           if(gm->isTimerActive())
               gm->stopTimer();
       }
       else
           gm->startTimer(100 * (gm->randInt(1,50)));
    }
    else
    {
       Ennemy *ennemy = new Ennemy();
       ennemy->setLevel(diffNiv);
       qWarning() << "An ennemy popped lvl" << diffNiv;

       ennemy->setPos(::sin((1 * 6.28) / 7) * 200,
                      ::cos((1 * 6.28) / 7) * 200);


       gm->addItemToScene(ennemy);

       _listeMichels.append(ennemy);

       if( _listeMichels.length() == EnnemyFactory::MAXENN)
       {
           if(gm->isTimerActive())
               gm->stopTimer();
       }
       else
           gm->startTimer(100 * (gm->randInt(1,50)));
    }
}


/**
 * @brief Retourne l'objet ennemy de la liste listeMichel en fonction de listpos
 * @param listpos position de l'ennemy dans la liste
 * @return l'objet ennemy
 */
Ennemy* EnnemyFactory::getEnnemyAt(int listpos)
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

    //qWarning() <<"nbmichel_indaListe :" <<  _listeMichels.length() ;
}

QList<Ennemy*> EnnemyFactory::getListMichel()
{
    return _listeMichels;
}
