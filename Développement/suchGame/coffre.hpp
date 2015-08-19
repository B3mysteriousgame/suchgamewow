#ifndef COFFRE_H
#define COFFRE_H


#include <QGraphicsItem>
#include <QGraphicsPixmapItem>


class Arme;
class Popup;
class Coffre : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)

public:
    Coffre();
    ~Coffre();

    bool ouvrir();
    void advance(int);
    Arme* getArme() const;

private:
    bool _isOpen;
    bool _ouvrable;
    Popup *_popup;
    Arme *_arme;
};

#endif // COFFRE_H
