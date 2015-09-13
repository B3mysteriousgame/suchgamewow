#include "panel.hpp"
#include "myview.hpp"

Panel::Panel(MyView *parentView) :
    QGraphicsRectItem()
{
    //QPoint vpos = parentView->ma;
    setPos(0,0);
    setBrush(QBrush(QColor().yellow()));
    setRect(0, 0, 100, 100);

    setVisible(true);
}



