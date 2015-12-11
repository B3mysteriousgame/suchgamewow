#include "ennemyfactory.h"
#include "barre.hpp"
#include <math.h>
#include "angleoperation.hpp"
#include "patate.hpp"
#include "gamemanager.hpp"
#include <QtDebug>
#include <QTimer>
#include <ennemylopette.h>

#define MAXENN 10

EnnemyFactory::EnnemyFactory()
    : QObject()
{
    _timerPopEnnemy = new QTimer();
    QObject::connect(_timerPopEnnemy, SIGNAL(timeout()), this, SLOT(createEnnemy()));

    //start();
}

EnnemyFactory::EnnemyFactory(EnnemyFactory *lol)
    : QObject(lol)
{}

EnnemyFactory::~EnnemyFactory()
{
    delete(_timerPopEnnemy);
}

void EnnemyFactory::createEnnemy()
{
    static const float diff = 0.1;
    static GameManager* const gm = GameManager::Instance();

    int diffNiv = (gm->getPatate())->getLvl();
    short plusOuMoins = gm->randInt(1,2);
    Ennemy *ennemy;
    static QString logmsg = "An ";

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
        ennemy = new EnnemyLopette();
        logmsg = " EnnemyLopette lvl ";
    }
    else
    {
       ennemy = new Ennemy();
       logmsg = " Ennemy lvl ";
    }

    ennemy->setLevel(diffNiv);
    //logmsg.append(diffNiv);



    ennemy->setPos(::sin((1 * 6.28) / 7) * 300,
                   ::cos((1 * 6.28) / 7) * 300);


    gm->addItemToScene(ennemy);

    _listeMichels.append(ennemy);

    if( _listeMichels.length() == MAXENN )
    {
         stop();
         qWarning() << "-------------------------------------too many ennemiys";
    }
    /* SEEMS WEIRD
    else
    {
        gm->startTimer(100 * (gm->randInt(1,50))); // Dafuh a gwan deh????
        GameManager::sta
    }
    */

    qWarning() << "-------" << _listeMichels.length();
    qWarning() << logmsg << diffNiv;
}


/**
 * @brief Retourne l'objet ennemy de la liste listeMichel en fonction de listpos
 * @param listpos position de l'ennemy dans la liste
 * @return l'objet ennemy
 */
Ennemy* EnnemyFactory::getEnnemyAt(int listpos) const
{
    return _listeMichels.at(listpos);
}

int EnnemyFactory::getNbEnnemy() const
{
    return _listeMichels.length();
}

void EnnemyFactory::removeEnnemy(Ennemy *it)
{
    _listeMichels.removeOne(it);

    //qWarning() <<"nbmichel_indaListe :" <<  _listeMichels.length() ;
}

//Gestion du timerPopEnnemy
bool EnnemyFactory::isTimerActive() const
{
    return _timerPopEnnemy->isActive();
}

void EnnemyFactory::stop()
{
    _timerPopEnnemy->stop();
}

void EnnemyFactory::startTimer(int ms)
{
    _timerPopEnnemy->start(ms);
}

void EnnemyFactory::start()
{
//    _timerPopEnnemy->start(1000 * 5);
    startTimer(100 * GameManager::randInt(1,50));
}
