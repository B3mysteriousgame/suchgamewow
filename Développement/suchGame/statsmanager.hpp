#ifndef STATSFRAME_HPP
#define STATSFRAME_HPP

#include "barre.hpp"

class QGraphicsScene;

class StatsManager
{
public:
    StatsManager(QGraphicsScene *scene);
    void moveBarresBy(const QPointF &dp);

signals:

public slots:

private:
    Barre _vie;
    Barre _mana;
};

#endif // STATSFRAME_HPP
