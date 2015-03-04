#ifndef PATATE_HPP
#define PATATE_HPP

#include <QGraphicsPixmapItem>
#include <QObject>
#include "personnage.hpp"

class Patate : public Personnage
{
    public:
        enum { Type = UserType + 4 };
        virtual int type() const{return Type;}

        Patate(QGraphicsItem *parent = 0);
        Patate(Patate *p);
        ~Patate();

        QList<QString> getSprites() const;
        int getImgCpt() const;

        void advance(int step);
        void avancer(short sens);
        void test();
        void attaque();
};
#endif // PATATE_HPP
