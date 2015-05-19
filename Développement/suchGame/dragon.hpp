#ifndef DRAGON_HPP
#define DRAGON_HPP

#include "ennemy.hpp"

class Dragon : public Ennemy
{

public:
    enum { Type = UserType + 5 }; // celui de ennemi
    virtual int type() const{return Type;}

    Dragon(short vie, short lvl, QGraphicsPixmapItem *parent = 0);
    Dragon(QGraphicsPixmapItem *parent);

};

#endif // DRAGON_HPP
