#include "dragon.hpp"

Dragon::Dragon(QGraphicsPixmapItem *parent) :
    Ennemy(parent)
{
    setPixmap(QPixmap(":dragon/images/Sprites/dragon/dragonD1.png"));

    if(_sm != NULL)
        delete(_sm);
    _sm = new SpriteManager(this, "dragon", 4);
}

Dragon::Dragon(short vie, short lvl, QGraphicsPixmapItem *parent) :
    Ennemy(vie, lvl, parent)
{
    setPixmap(QPixmap(":dragon/images/Sprites/dragon/dragonD1.png"));

    if(_sm != NULL)
        delete(_sm);

    setPos(500, 300);
    _sm = new SpriteManager(this, "dragon", 4);
}
