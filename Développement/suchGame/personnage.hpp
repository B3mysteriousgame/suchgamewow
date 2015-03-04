#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class GameManager;

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
    int getFullHealth() const;
    void setFullHealth(const int health);
    int getActualHealth() const;
    void setActualHealth(const int health);
    QPointF center() const;

    void loseHealth(int degats);
    void calculResistance();

    virtual void advance(int step) = 0;

    virtual void test(){}
    virtual void attaque() = 0;

protected:
    qreal _speed;
    int _imgCpt;
    int _sens; // 0=gauche; 1=haut; 2=droite; 3=bas;
    int _actualhealth;
    int _fullhealth;
    int _resistance;
    QList<QString> _sprites;
    GameManager *_gm;

};

#endif // PERSONNAGE_H
