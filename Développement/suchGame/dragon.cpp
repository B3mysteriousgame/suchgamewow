#include "dragon.hpp"

Dragon::Dragon(QGraphicsPixmapItem *parent) :
    Ennemy(parent)
{
    setPixmap(QPixmap(":dragon/images/Sprites/dragon/dragonD1.png"));

    if(_sm != NULL)
        delete(_sm);

    setPos(500, 300);
    setLevel(5);
    _sm = new SpriteManager(this, "dragon", 4);
}

Dragon::Dragon(short lvl, QGraphicsPixmapItem *parent) :
    Ennemy(lvl, parent)
{
    setPixmap(QPixmap(":dragon/images/Sprites/dragon/dragonD1.png"));

    if(_sm != NULL)
        delete(_sm);

    setPos(500, 300);
    setLevel(lvl);
    _sm = new SpriteManager(this, "dragon", 4);
}

void Dragon::setLevel(const int lvl)
{
    _lvl = lvl;
    _xpDon = (30 + (9 * (_lvl - 1))) * 2.5;
    _fullhealth = 750 + (12 * (_lvl - 1));
    _actualhealth = _fullhealth;
    _atk = 80 + (20 * (_lvl - 1));
    _def = 30 + (16 * (_lvl - 1));
}
