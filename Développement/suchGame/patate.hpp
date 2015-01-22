#ifndef PATATE_HPP
#define PATATE_HPP

#include <QGraphicsPixmapItem>
#include <QObject>

class Patate : public QGraphicsPixmapItem
{
    //Q_OBJECT

    public:
        enum { GAUCHE, HAUT, DROITE, BAS };
        enum { Type = UserType + 4 };
        virtual int type() const{return Type;}

        Patate(QGraphicsItem *parent = 0);
        Patate(Patate *p);

        QList<QString> getSprites() const;
        int getImgCpt() const;
        int getSens() const;
        void setSens(const short sens);

        void advance(int step);
        void test();

    private:
        int _imgCpt;
        int _sens; // 0=gauche; 1=haut; 2=droite; 3=bas;


        QList<QString> _sprites;
};
#endif // PATATE_HPP
