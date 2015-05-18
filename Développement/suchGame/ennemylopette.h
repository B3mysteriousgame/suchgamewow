#ifndef ENNEMYLOPETTE_H
#define ENNEMYLOPETTE_H

#include "ennemy.hpp"
#include <QPointF>


class EnnemyLopette: public Ennemy
{
public:
    EnnemyLopette();
    ~EnnemyLopette();

    void fuite();
    QPointF chercheCloche();
    void setFuite(bool fuite);
    void advance(int step);

private:
   int _vitessefuite;
   bool _enfuite;

};

#endif // ENNEMYLOPETTE_H
