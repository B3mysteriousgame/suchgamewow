#ifndef ITEM_H
#define ITEM_H


#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

#include "popup.hpp"
#include "gamemanager.hpp"

class GameManager;

class Item : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)

    public:
        enum { Type = UserType + 8 };
        virtual int type() const{return Type;}

        Item(QGraphicsItem *parent = 0);
        ~Item();
        virtual void advance(int) = 0;
        QPixmap get_pixmap() const;
        QString get_nom() const;
        void set_nom(const QString& nom);

    protected:
        int _atq;
        int _def;
        int _portee;
        bool _ramassable;
        Popup *_popup; // pas oublier de delete ds destructeur!!!
        QString _nom;
        QPixmap _pixmap;
};

#endif // ITEM_H
