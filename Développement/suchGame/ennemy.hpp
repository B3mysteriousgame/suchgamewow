#ifndef ENNEMY_H
#define ENNEMY_H


#include <QGraphicsItem>
#include "personnage.hpp"

class Barre;

class Strategie;
class Ennemy : public Personnage
{
    public:
        /* Définition du type d'objet */
        enum { Type = UserType + 5 };
        virtual int type() const{return Type;}

        Ennemy(QGraphicsItem *parent = 0);
        Ennemy(const Ennemy& e);
        ~Ennemy();

        int getXpDon() const;
        void loseHealth(int degats);
        void advance(int step);
        void attaque(){}
        bool touched(){ return _touched; }
        void setTouched(bool t){ _touched = t; }
        Barre* getBarre();

    private:
        void doStrat();
        Barre *_barre;
        bool _touched;
        int _xpDon;
        Strategie *_strat;
};

#endif // ENNEMY_H
