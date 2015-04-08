 #ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QStateMachine>
#include <QState>

class GameManager;

class Personnage : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    enum { GAUCHE, HAUT, DROITE, BAS };
    enum { Type = UserType + 3 };
    virtual int type() const{return Type;}

    Personnage(QGraphicsItem* parent = 0);
    Personnage(Personnage*){}
    ~Personnage(){}

    virtual QList<QString> getSprites() const{ return QList<QString>(); }
    virtual int getImgCpt() const{ return _imgCpt; }
    int getSens() const;
    void setSens(const short sens);
    qreal getSpeed() const;
    void setSpeed(const qreal val);
    int getAtk() const { return _atk; }
    void setAtk(const int nuAtk) { _atk = nuAtk; }
    void addAtk(const int atk) { _atk += atk; }
    int getFullHealth() const;
    void setFullHealth(const int health);
    int getActualHealth() const;
    void setActualHealth(const int health);
    QPointF center() const;

    void loseHealth(int degats);
    qreal getPourcentageVie();
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
    int _def;
    int _atk;
    int _mana;
    QList<QString> _sprites;
    GameManager *_gm;
    QStateMachine _stateMachine;
    QState shaut;
    QState sbas;
    QState sgauche;
    QState sdroite;
    QState sidle;

    virtual void initStates();

};

#endif // PERSONNAGE_H
