#include <QDebug>
#include "panel.hpp"
#include "myview.hpp"

Panel::Panel(MyView *parentView) :
    QGraphicsRectItem(),
    _view(parentView)
{
    setBrush( * new QBrush(Qt::yellow) );
    //setPos(70, 75);
    setRect(0, 0, 700, 350);
    setZValue(20);


    setVisible(true);
}

Panel::~Panel()
{
    foreach (QGraphicsItem *item, _items)
    {
        delete(item);
    }
    //_items.clear();
}

void Panel::addItem(QGraphicsItem *item)
{
    qWarning() << _view->mapFromScene(pos());
    //item->moveBy(x(), y());
    item->setParentItem(this);
    _items.append(item);
}

/*
void Panel::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush( QBrush(QColor().yellow()) );
    painter->drawRect(0, 0, 100, 100);
}
*/
