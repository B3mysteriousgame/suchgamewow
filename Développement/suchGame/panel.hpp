#ifndef PANEL_H
#define PANEL_H
#include <QGraphicsRectItem>

class MyView;

class Panel : public QGraphicsRectItem
{
    public:
        Panel(MyView *parentView);
};

#endif // PANEL_H
