#ifndef POPUP_H
#define POPUP_H

#include <QGraphicsItem>
#include <personnage.hpp>
#include <QPainter>
#include <personnage.hpp>
#include <ennemy.hpp>
#include <QObject>


class Popup : public QObject, public QGraphicsItem
{

public:
    Popup(QGraphicsItem *parent);
    ~Popup();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QRectF boundingRect() const;
protected:
    QGraphicsItem *_parent;
};

#endif // POPUP_H
