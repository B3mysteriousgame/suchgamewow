#ifndef STRAT1_H
#define STRAT1_H

#include "strategie.hpp"

class Strat1 : public Strategie
{
    public:
        ~Strat1();
    private:
        void analyser ();
        void appliquer ();
};
#endif // STRAT1_H
