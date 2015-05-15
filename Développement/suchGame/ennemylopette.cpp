#include "ennemylopette.h"
#include "ennemy.hpp"
#include "gamemanager.hpp"
#include "mouse.h"
#include "movefreelystrat.hpp"
#include "strat1.hpp"
#include "strat2.hpp"
#include<QDebug>
#include "barre.hpp"
#include <QList>

EnnemyLopette::EnnemyLopette()
    //Ennemy(parent)
{
    _enfuite = false;
    _vitessefuite = _speed * 1,5;
}

EnnemyLopette::~EnnemyLopette()
{

}

void EnnemyLopette::advance(int step)
{
    if(getActualHealth() <= (getFullHealth()/3))
        _enfuite=true;

    if(_enfuite == false)
    {
        Ennemy::advance(step);
    }
    else
    {
         QPointF pointcloche = QPointF(50,100); // A remplacer par la position de la cloche la plus proche
        _strat = new Strat2(this,pointcloche);
        _strat->executer();

    }
}

void EnnemyLopette::setFuite(bool fuite)
{
    _enfuite = fuite;
}


