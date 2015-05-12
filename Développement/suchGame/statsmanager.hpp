#ifndef STATSFRAME_HPP
#define STATSFRAME_HPP

#include "barre.hpp"

class QGraphicsScene;

class StatsManager
{
public:
    StatsManager(QGraphicsScene *scene);
    ~StatsManager();
    void moveBarresBy(const QPointF &dp);
    void setLargeurVie(int lvie);
    void setLargeurMana(int lmana);

signals:

public slots:

private:
    Barre *_vie;
    Barre *_mana;
};

#endif // STATSFRAME_HPP
