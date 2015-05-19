#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QPropertyAnimation>
#include <QTimer>
#include "spritemanager.hpp"

class GameManager;

class Personnage : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)

    public:
        enum { GAUCHE, HAUT, DROITE, BAS };
        enum { Type = UserType + 3 };
        virtual int type() const{return Type;}


        Personnage(QGraphicsItem* parent = 0);
        Personnage(Personnage*){}
        ~Personnage();

        QList<QString> getSprites() const{ return QList<QString>(); }
        int getImgCpt() const{ return _imgCpt; }
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
        bool isTargetable() const { return _targetable; }
        QString getStrSens() const;
        QPointF center() const;
        int getLvl() const { return _lvl; }

        void loseHealth(int degats);
        qreal getPourcentageVie();
        void calculResistance();

        bool isMovin() const;
        void setMovin(const bool move);
        inline bool operator==(const Personnage &p) const;
        inline bool operator!=(const Personnage &p) const;


        virtual void advance(int step) = 0;

    virtual void test(){}
    virtual void attaque() = 0;
    void ChangeSensEtDeplacement();
    void MoveToDest(QPointF pointDest);
    void setVisible(bool vis);
    signals:
        void statChanged(const int, const QString&);
        void moveChanged();
        void deadPerso();

    protected:
        qreal _speed;
        int _imgCpt;
        int _sens; // 0=gauche; 1=haut; 2=droite; 3=bas;
        int _actualhealth;
        int _fullhealth;
        int _def;
        int _atk;
        int _mana;
        int _fullmana;
        QList<QString> _sprites;
        GameManager *_gm;
        bool _movin;
        SpriteManager *_sm;
        int _lvl;
        bool _targetable;
        QTimer *_timerTargetable;
        short _timout;

        virtual void initStates();
        void initAnim();
        virtual void setTargetable(bool targetable);

    protected slots:
        void setTargetable() { setTargetable(true); }
        virtual void startKiCharge(){}
        virtual void stopKiCharge(){}
        virtual void rechargKi(){}

};

#endif // PERSONNAGE_H
