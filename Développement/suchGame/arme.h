#ifndef ARME_H
#define ARME_H


#include <QGraphicsPixmapItem>

#include <QGraphicsItem>

class Arme : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)

    public:
        Arme();
        int get_atq() const;
        int get_def() const;
        int get_portee() const;
        QString get_nom();
        QPixmap get_pixmap();
        void set_atq(int atq);
        void set_def(int def);
        void set_portee(int portee);
        void set_nom(QString nom);

    protected:
        int _atq;
        int _def;
        int _portee;
        QString _nom;
        QPixmap _pixmap;
};

#endif // ARME  _H
