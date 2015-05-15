#include "statsframe.hpp"
#include <QGraphicsScene>

StatsManager::StatsManager(QGraphicsScene *scene) :
    _vie(true),
    _mana(true)
{
    QPointF p(50,50);
    int marginBetween = 40;
    const short largeur = 100, hauteur = 10;

    _vie.setColor(QColor(Qt::red));
    _vie.setPos(p);
    _vie.setHauteur(hauteur);
    _vie.setLargeur(largeur);
    _vie.setZValue(20000);

    p.ry() += marginBetween;

    _mana.setColor(QColor(Qt::blue));
    _mana.setPos(p);
    _mana.setHauteur(hauteur);
    _mana.setLargeur(largeur);
    _mana.setZValue(20000);
    /*
    _vie.show();
    _mana.show();
    */

    scene->addItem(&_vie);
    scene->addItem(&_mana);
}
