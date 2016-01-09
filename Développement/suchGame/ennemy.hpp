#ifndef ENNEMY_H
#define ENNEMY_H


#include <QGraphicsItem>
#include "personnage.hpp"
#include <QGraphicsPixmapItem>
#include "barre.hpp"
#include "strategie.hpp"

class Barre;

class Strategie;
class Ennemy : public Personnage
{

    public:
        /* Définition du type d'objet */
        enum { Type = UserType + 5 };
        virtual int type() const{return Type;}

        Ennemy(QGraphicsItem *parent = 0);
        Ennemy(short lvl, QGraphicsItem *parent = 0);
        Ennemy(const Ennemy& e);
        ~Ennemy();

        int getXpDon() const;
        void loseHealth(const int degats);
        void advance(int step);
        void attaque(){}
        bool touched() const { return _touched; }
        void setTouched(bool t){ _touched = t; }
        Barre* getBarre() const;
        void handleSceneBounder();
        QString changeSens(QString lepath);
        void hidePointAggro();
        void showPointAggro();
        virtual void setLevel(const int lvl);


    protected:
        void doStrat();
        void initAnimation();
        Barre *_barre;
        bool _touched;
        int _xpDon;
        Strategie *_strat;
        bool _patateproche;
        QGraphicsPixmapItem *_pointAggro;

        void setTargetable(bool targetable);


};

#endif // ENNEMY_H
