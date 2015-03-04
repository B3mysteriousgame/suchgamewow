#ifndef MOVEFREELYSTRAT_HPP
#define MOVEFREELYSTRAT_HPP

#include "strategie.hpp"

class Ennemy;
class Ball;

class MoveFreelyStrat : public Strategie
{
    public:
        MoveFreelyStrat(Ennemy *parent);
        ~MoveFreelyStrat();
    private:
        void analyser ();
        void appliquer ();
        void doStrat();
        void doBallStrat(Ball *item);
        Ennemy *_parent;
};

#endif // MOVEFREELYSTRAT_HPP
