#include "item.hpp"
#include "personnage.hpp"



Item::Item(QGraphicsItem *parent):
    QObject(),
    QGraphicsPixmapItem(parent),
    _ramassable(false)
{
    _popup = new Popup(this);
    _popup->moveBy(10,-15);
}

Item::~Item()
{
    delete(_popup);
}

QPixmap Item::get_pixmap() const
{
    return _pixmap;
}


void Item::set_nom(const QString& nom)
{
    _nom = nom;
}

QString Item::get_nom() const
{
    return _nom ;
}
