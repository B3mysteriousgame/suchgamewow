#ifndef STRAT2_H
#define STRAT2_H

#include "strategie.hpp"
#include "QPointF"

class Ennemy;

class Strat2 : public Strategie
{
    public:
        Strat2(Ennemy* parent, QPointF dest);
        ~Strat2 ();

    private:
        void analyser ();
        void appliquer ();
        Ennemy *_parent;
        QPointF _dest;
        bool _clocheproche;
};
#endif // STRAT2_H
