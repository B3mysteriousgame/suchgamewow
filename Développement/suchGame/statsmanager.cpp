#include "statsmanager.hpp"
#include "myview.hpp"
#include "gamemanager.hpp"
#include <QGraphicsScene>
#include <QDebug>

StatsManager::StatsManager(QGraphicsScene *scene)
{
    QPointF p(25,25);
    int marginBetween = 20;
    const short largeur = 100, hauteur = 10;

    _vie = new Barre(true);
    _mana = new Barre(true);

    _vie->setColor(QColor(Qt::red));
    _vie->setPos(p);
    _vie->setHauteur(hauteur);
    _vie->setLargeur(largeur);
    _vie->setZValue(20000);

    p.ry() += marginBetween;

    _mana->setColor(QColor(Qt::blue));
    _mana->setPos(p);
    _mana->setHauteur(hauteur);
    _mana->setLargeur(largeur);
    _mana->setZValue(20000);
    /*
    _vie->show();
    _mana->show();
    */

    scene->addItem(_vie);
    scene->addItem(_mana);
}

StatsManager::~StatsManager()
{
    delete(_vie);
    delete(_mana);
}

void StatsManager::moveBarresBy(const QPointF &dp)
{
    static bool firstTime = true;
    qreal dx, dy;

    dx = dp.x() * -1;
    dy = dp.y() * -1;

    if(firstTime)
        firstTime = false;
    else
    {
        if(dx != 0 || dy != 0)
        {
            //qWarning() << "dpos:" << dx << dy << dp;
            _vie->moveBy(dx, dy);
            _mana->moveBy(dx, dy);
        }
    }
}

void StatsManager::setLargeurVie(int lvie)
{
    _vie->setLargeur(lvie);
}

void StatsManager::setLargeurMana(int lmana)
{
    _mana->setLargeur(lmana);
}
