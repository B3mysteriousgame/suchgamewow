#include "popup.hpp"

Popup::Popup(QGraphicsItem *parent):
    QObject(),
    QGraphicsItem()
{
    _parent = parent;
}

Popup::~Popup()
{

}

void Popup::paint(QPainter *lepainter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    lepainter->setBrush(QColor(Qt::gray));
    QRectF rect = QRectF(1,1,20,20);
    lepainter->drawRect(rect);
    lepainter->drawText(rect.center(),"F");
}

QRectF Popup::boundingRect() const
{
    QRectF rect = QRectF(0,0,1,1);

    return rect;
}

