#ifndef PATATE_HPP
#define PATATE_HPP

#include <QGraphicsPixmapItem>
#include <QObject>

class Patate : public QGraphicsPixmapItem
{
    //Q_OBJECT

    public:
        enum { GAUCHE, HAUT, DROITE, BAS };

        Patate(QGraphicsItem *parent = 0);
        Patate(Patate *p);

        QList<QString> getSprites() const;
        int getImgCpt() const;
        void advance(int step);

        enum { Type = UserType + 4 };
        virtual int type() const{return Type;}

    private:
        int _imgCpt;
        int _sens; // 0=gauche; 1=haut; 2=droite; 3=bas;


        QList<QString> _sprites;
};
#endif // PATATE_HPP
