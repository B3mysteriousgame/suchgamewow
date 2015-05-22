#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QGraphicsPixmapItem>

class Obstacle : public QGraphicsPixmapItem
{

public:
    Obstacle();
    ~Obstacle();
    enum { Type = UserType + 7 };
    virtual int type() const{return Type;}
};

#endif // OBSTACLE_H
