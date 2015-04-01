#ifndef MAP_H
#define MAP_H

#include <QGraphicsItem>
#include <QGraphicsScene>

class Map : public QGraphicsScene
{

    public:
        Map();

    protected:
        QGraphicsPixmapItem _grass;
};

#endif // MAP_H
