#ifndef COFFRE_H
#define COFFRE_H


#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include "arme.h"
#include "gamemanager.hpp"
#include <popup.hpp>


class Coffre : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)

public:
    Coffre();
    ~Coffre();

    bool ouvrir();
    void advance(int phase);
    Arme * getArme();

private:
    bool _isOpen;
    Arme* _arme;
    bool _ouvrable;
    Popup *_popup;
};

#endif // COFFRE_H
