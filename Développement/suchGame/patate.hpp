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

    private:
        void stayInScene();
        void stayInView();
        bool scrollView(const short lastBlockinDir);
        bool isNearSceneBorder() const;

        // permet de savoir de quel cote est le bord
        //  si on est dans une "case bordure"
        //  (-1 non, 0 bordure gauche, 1 bordure haut, etc...)
        short _blockinCase;
        short _blockinBorder;
};
#endif // PATATE_HPP
