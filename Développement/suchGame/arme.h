#ifndef ARME_H
#define ARME_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

#include "popup.hpp"
#include "gamemanager.hpp"
#include "item.hpp"

class GameManager;

class Arme : public Item
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)

    public:
        enum { Type = UserType + 9 };
        virtual int type() const{return Type;}

        Arme();
        ~Arme();
        void advance(int);
        int get_atq() const;
        int get_def() const;
        int get_portee() const;
        QPixmap get_pixmap() const;
        void set_atq(const int atq);
        void set_def(const int def);
        void set_portee(const int portee);

    protected:
        int _atq;
        int _def;
        int _portee;
        bool _ramassable;
        Popup *_popup; // pas oublier de delete ds destructeur!!!
        QString _nom;
        QPixmap _pixmap;
};

#endif // ARME  _H
