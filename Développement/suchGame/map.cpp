#include "map.h"
#include "obstacle.h"
#include "iostream"
#include "gamemanager.hpp"
#include <QDebug>

Map::Map() :
    QGraphicsScene()
{
    _scene = new QGraphicsScene();
    _scene->setSceneRect(-230, -130, 936, 555);
    _scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    // test obstacle

    _obstacle = new Obstacle();
    _obstacle->setPixmap(QPixmap(":/images/Sprites/obstacle.png"));
    GameManager::Instance()->addItemToScene(_obstacle);
    qWarning() << "obstacle added";
    _obstacle->setActive(true);
    _obstacle->setPos(200,200);
}
