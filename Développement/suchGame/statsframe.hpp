#ifndef STATSFRAME_HPP
#define STATSFRAME_HPP

#include "barre.hpp"

class QGraphicsScene;

class StatsManager
{
public:
    StatsManager(QGraphicsScene *scene);

signals:

public slots:

private:
    Barre _vie;
    Barre _mana;
};

#endif // STATSFRAME_HPP
