#ifndef PERSO_HPP
#define PERSO_HPP

#include "mouse.h"
#include <QList>
#include "ball.hpp"

class Perso : public Mouse
{
    public:
        enum { Type = UserType + 2 };

        Perso();
        ~Perso();
        void avancer();
        void addAngle(qreal a);
        qreal getSpeed() const;
        void attaque();
        QPointF getCenter() const;
        QPointF getSceneCenter() const;
        QRectF boundingRect() const;
        QPainterPath shape() const;

        int type() const{return Type;}

    private:
        void advance(int step);
        QList<Ball*> balls;
};

#endif // PERSO_HPP
