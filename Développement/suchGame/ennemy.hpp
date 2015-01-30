#ifndef ENNEMY_H
#define ENNEMY_H


#include <QGraphicsItem>
#include "personnage.hpp"

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

    private:
        void doStrat();

        bool _touched;
};

#endif // ENNEMY_H
