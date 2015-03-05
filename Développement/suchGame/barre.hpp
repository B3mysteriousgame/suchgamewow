#ifndef BARRE_H
#define BARRE_H

#include <QGraphicsItem>
#include <personnage.hpp>
#include <QPainter>
#include <personnage.hpp>
#include <ennemy.hpp>


class Barre : public QGraphicsItem
{
public:
    Barre();
    ~Barre();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void setColor(QColor color);
    QColor getColor() const;
    QRectF boundingRect() const;

    void setLargeur(qreal largeur){
        _largeur = largeur;
    }

protected:
    QColor _color;
    qreal  _largeur;
};
#endif // BARRE_H
