#ifndef DRAGON_HPP
#define DRAGON_HPP

#include "ennemy.hpp"

class Dragon : public Ennemy
{

public:
    enum { Type = UserType + 5 }; // celui de ennemi
    virtual int type() const{return Type;}

    Dragon(QGraphicsPixmapItem *parent = 0);
    Dragon(short lvl, QGraphicsPixmapItem *parent = 0);
    void setLevel(const int lvl);
};

#endif // DRAGON_HPP
