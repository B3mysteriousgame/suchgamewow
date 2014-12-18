#ifndef PATATE_HPP
#define PATATE_HPP

#include <QGraphicsPixmapItem>
#include <QObject>

class Patate : public QGraphicsPixmapItem
{
    //Q_OBJECT

    public:
        Patate(QString path, QGraphicsItem *parent = 0);

        enum { Type = UserType + 4 };
        virtual int type() const{return Type;}

    private:
        QString _imgPath;
};

#endif // PATATE_HPP
