#ifndef MAP_H
#define MAP_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include "myview.hpp"

class Map : public QGraphicsScene
{

    public:
        Map();


    private:
        QGraphicsScene *_scene;
        MyView *_view;
        QTimer *_timer;
        QTimer *_timerLvlUp;
        QTimer *_timerPopEnnemy;

    protected:
        QGraphicsPixmapItem _grass;
        QGraphicsPixmapItem _background;
};

#endif // MAP_H
