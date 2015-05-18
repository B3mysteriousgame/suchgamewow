#ifndef STRAT1_H
#define STRAT1_H

#include "strategie.hpp"
#include <QPointF>

class Ennemy;
class Patate;

class Strat1 : public Strategie
{
    public:
        Strat1(Ennemy *parent);
        ~Strat1();
    private:
        void analyser ();
        void appliquer ();
        Ennemy *_parent;
};
#endif // STRAT1_H
