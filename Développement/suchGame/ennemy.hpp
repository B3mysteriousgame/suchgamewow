#ifndef ENNEMY_H
#define ENNEMY_H


#include <QGraphicsItem>
#include "personnage.hpp"

class Ennemy : public Personnage
{
public:
    /* Définition du type d'objet */
    enum { Type = UserType + 6 };
    virtual int type() const{return Type;}

    Ennemy(QGraphicsItem *parent = 0);
    ~Ennemy();

    QList<QString> getSprites() const{}
    int getImgCpt() const;
    int getSens() const;
    void setSens(const short sens);

    void advance(int step);
};

#endif // ENNEMY_H
