#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Personnage : public QGraphicsPixmapItem
{
public:
    enum { GAUCHE, HAUT, DROITE, BAS };
    enum { Type = UserType + 5 };
    virtual int type() const{return Type;}

    Personnage(QGraphicsItem *parent = 0){}
    Personnage(Personnage *p){}
    ~Personnage(){}

    virtual QList<QString> getSprites() const{}
    virtual int getImgCpt() const{}
    int getSens() const;
    void setSens(const short sens);

    virtual void advance(int step) = 0;

    virtual void test(){}

protected:
    int _imgCpt;
    int _sens; // 0=gauche; 1=haut; 2=droite; 3=bas;
    QList<QString> _sprites;

};

#endif // PERSONNAGE_H
