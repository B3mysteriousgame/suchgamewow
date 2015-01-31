#ifndef ENNEMY_H
#define ENNEMY_H


#include <QGraphicsItem>
#include "personnage.hpp"

class Strategie;
class Ennemy : public Personnage
{
    public:
        /* Définition du type d'objet */
        enum { Type = UserType + 5 };
        virtual int type() const{return Type;}

        Ennemy(QGraphicsItem *parent = 0);
        ~Ennemy();

        void advance(int step);
        void attaque(){}
        bool touched(){ return _touched; }
        void setTouched(bool t){ _touched = t; }

    private:
        void doStrat();

        bool _touched;
        Strategie *_strat;
};

#endif // ENNEMY_H
