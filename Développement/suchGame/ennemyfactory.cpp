#include "ennemyfactory.h"
#include "barre.hpp"

EnnemyFactory::EnnemyFactory(GameManager gm)
{
    _gm = gm;
}

EnnemyFactory::~EnnemyFactory()
{

}

EnnemyFactory::createEnnemy()
{
    Ennemy *ennemy = new Ennemy();
    ennemy->setPos(::sin((1 * 6.28) / MouseCount) * 200,
                   ::cos((1 * 6.28) / MouseCount) * 200);
    Barre *barre = ennemy->getBarre();
    barre->moveBy(-12,-15);
    barre->setParentItem(ennemy);

    QGraphicsScene scene = _gm.getScene();
    scene->addItem(ennemy);
    scene->addItem(barre);

}

