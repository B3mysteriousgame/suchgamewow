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

    void ouvrir();
    void advance(int phase);

private:
    bool _isOpen;
    Arme* _arme;
    bool _ouvrable;
    Popup *_popup;
};

#endif // COFFRE_H
