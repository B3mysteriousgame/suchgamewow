#include "map.h"

Map::Map() :
    QGraphicsScene()
{
    _scene = new QGraphicsScene();
    _scene->setSceneRect(-230, -130, 936, 555);
    _scene->setItemIndexMethod(QGraphicsScene::NoIndex);
}
