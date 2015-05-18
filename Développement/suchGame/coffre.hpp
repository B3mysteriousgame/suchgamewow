#ifndef COFFRE_H
#define COFFRE_H


#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include "arme.h"
#include "gamemanager.hpp"


class Coffre : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)

public:
    Coffre();
    ~Coffre();

    void ouvrir();

private:
    bool _isOpen;
    Arme* _arme;
};

#endif // COFFRE_H
