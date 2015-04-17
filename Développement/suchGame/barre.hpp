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
    Barre(bool estPatate);
    ~Barre();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void setColor(QColor color);
    QColor getColor() const;
    QRectF boundingRect() const;

    void setLargeur(qreal largeur);
    qreal getLargeur();
    void setHauteur(qreal hauteur);
    qreal getHauteur();

protected:
    QColor _color;
    qreal  _largeur;
    qreal  _hauteur;
    qreal  _largeurInit;
    qreal  _hauteurInit;
};
#endif // BARRE_H
