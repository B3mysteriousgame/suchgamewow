#ifndef STRAT2_H
#define STRAT2_H

#include "strategie.hpp"

class Strat2 : public Strategie
{
    public:
        ~Strat2 ();

    private:
        void analyser ();
        void appliquer ();
};
#endif // STRAT2_H
