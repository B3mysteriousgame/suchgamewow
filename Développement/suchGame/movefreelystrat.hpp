#ifndef MOVEFREELYSTRAT_HPP
#define MOVEFREELYSTRAT_HPP

#include "strategie.hpp"

class Ennemy;
class MoveFreelyStrat : public Strategie
{
    public:
        MoveFreelyStrat(Ennemy *parent);
        ~MoveFreelyStrat();
    private:
        void analyser ();
        void appliquer ();
        void doStrat();
        Ennemy *_parent;
};


#endif // MOVEFREELYSTRAT_HPP
