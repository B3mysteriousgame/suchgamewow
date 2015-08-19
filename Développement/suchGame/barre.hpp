#ifndef BARRE_H
#define BARRE_H

#include <QGraphicsItem>
#include <personnage.hpp>
#include <QPainter>
#include <personnage.hpp>
#include <ennemy.hpp>
#include <QObject>


class Barre : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    Barre(bool estPatate);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void setColor(const QColor color);
    QColor getColor() const;
    void setAlpha(const int a);
    QRectF boundingRect() const;

    void setLargeur(const qreal plargeur);
    qreal getLargeur() const ;
    void setHauteur(const qreal hauteur);
    qreal getHauteur() const;

protected:
    QColor _color;
    QColor _bkColor;
    qreal  _largeur;
    qreal  _hauteur;
    qreal  _largeurInit;
    qreal  _hauteurInit;
    QTimer _effectTimer;

private slots:
    void stopEffect();
};
#endif // BARRE_H
