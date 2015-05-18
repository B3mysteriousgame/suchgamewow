#include "ennemyfactory.h"
#include "barre.hpp"
#include <math.h>
#include "angleoperation.hpp"
#include "patate.hpp"
#include "gamemanager.hpp"
#include <QtDebug>
#include <QTimer>

EnnemyFactory::EnnemyFactory()
    : QObject()
{
    _timerPopEnnemy = new QTimer();
    QObject::connect(_timerPopEnnemy, SIGNAL(timeout()), this, SLOT(createEnnemy()));

    start();
}

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

    Ennemy *ennemy = new Ennemy(diffNiv);
    ennemy->setPos(::sin((1 * 6.28) / 7) * 200,
                   ::cos((1 * 6.28) / 7) * 200);

    Barre *barre = ennemy->getBarre();
    barre->moveBy(-4,0);
    barre->setParentItem(ennemy);

    gm->addItemToScene(ennemy);

    _listeMichels.append(ennemy);

    if( _listeMichels.length() == EnnemyFactory::MAXENN)
    {
        if(isTimerActive())
            stopTimer();
    }
    else
        startTimer(100 * (gm->randInt(1,50)));

    qWarning() << "An ennemy popped lvl" << diffNiv;
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

//Gestion du timerPopEnnemy
bool EnnemyFactory::isTimerActive()
{
    return _timerPopEnnemy->isActive();
}

void EnnemyFactory::stopTimer()
{
    _timerPopEnnemy->stop();
}

void EnnemyFactory::startTimer(int ms)
{
    _timerPopEnnemy->start(ms);
}

void EnnemyFactory::start()
{
    _timerPopEnnemy->start(1000 * 5);
}
