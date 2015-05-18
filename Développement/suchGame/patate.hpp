#ifndef PATATE_HPP
#define PATATE_HPP

#include <QGraphicsPixmapItem>
#include <QObject>
#include "personnage.hpp"

class Patate : public Personnage
{
    public:
        enum { Type = UserType + 4 };
        virtual int type() const{return Type;}

        Patate(QGraphicsItem *parent = 0);
        Patate(Patate *p);
        ~Patate();

        QList<QString> getSprites() const;
        int getImgCpt() const;

        //void setSens(const short sens) override;
        void advance(int step);
        void avancer(short sens);
        void test();
        void attaque();
        void handlePosLimits();
        void setXp(const int xp);
        void addXp(const int xp);
        void lvlUp();
        void initStates();
        QString getStrSens() const;
        void loseHealth(int degats);
        bool isCharginKi() const { return _charginKi; }
        void setCharginKi(bool is);
        void quickPunch();

    signals:
        //void deadPerso();
        //void kiChanged(int);

    private slots:
        void startKiCharge();
        void stopKiCharge();
        void rechargKi();

protected slots:
    void hidePointAggro(){}

    private:
        void stayInScene();
        void stayInView();
        bool scrollView();
        bool isNearSceneBorder() const;
        void loseMana(int mana);
        void loseKi(qreal ki);

        // permet de savoir de quel cote est le bord
        //  si on est dans une "case bordure"
        //  (-1 non, 0 bordure gauche, 1 bordure haut, etc...)
        short _blockinCase;
        short _blockinBorder;
        int _xp;
        int _xpMax;
        int _lvl;

        int _fullki;
        int _ki;
        bool _charginKi;
        QTimer *_timerKiCharg;
};
#endif // PATATE_HPP
