#ifndef COFFRE_H
#define COFFRE_H


#include <QGraphicsItem>
#include <QGraphicsPixmapItem>


class Item;
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
    Item* getItem() const;

private:
    bool _isOpen;
    bool _ouvrable;
    Popup *_popup;
    Item *_item;
};

#endif // COFFRE_H
