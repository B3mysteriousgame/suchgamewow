#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Personnage : public QGraphicsPixmapItem
{
public:
    enum { GAUCHE, HAUT, DROITE, BAS };
    enum { Type = UserType + 3 };
    virtual int type() const{return Type;}

    Personnage(QGraphicsItem *parent = 0){}
    Personnage(Personnage *p){}
    ~Personnage(){}

    virtual QList<QString> getSprites() const{}
    virtual int getImgCpt() const{}
    int getSens() const;
    void setSens(const short sens);
    qreal getSpeed() const;
    void setSpeed(const qreal val);
    QPointF center() const;

    virtual void advance(int step) = 0;

    virtual void test(){}
    virtual void attaque() = 0;

protected:
    qreal _speed;
    int _imgCpt;
    int _sens; // 0=gauche; 1=haut; 2=droite; 3=bas;
    QList<QString> _sprites;

};

#endif // PERSONNAGE_H
