#include "patate.hpp"

Patate::Patate(QString path, QGraphicsItem *parent)
    : QGraphicsPixmapItem(path, parent)
{
    // ":/images/patate.png"
    _imgPath = path;
    /*
    setPos(10, 10);

    show();
    */
}
/*
Patate::Patate(const Patate& p)
    : QGraphicsPixmapItem(p.parentItem())
{
    setPixmap(p.pixmap());
    _imgPath = p.getImgPath();

    show();
}

const QString& Patate::getImgPath() const
{
    return _imgPath;
}

void Patate::advance(int step)
{
}

QRectF Patate::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(x() - adjust, y() - adjust,
                  pixmap().width() + adjust * 2, pixmap().height() + adjust * 2);
}
QPainterPath Patate::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());

    return path;
}
void Patate::paint(QPainter *painter, const QStyleOptionGraphicsItem *sogi,
           QWidget *wid)
{

}

QPointF Patate::center() const
{
    return QPointF(boundingRect().x() + boundingRect().width() / 2,
                       boundingRect().y() + boundingRect().height() / 2 - 7);

}
*/
