#ifndef PANEL_H
#define PANEL_H
#include <QGraphicsRectItem>

class MyView;

class Panel : public QGraphicsRectItem
{
    public:
        Panel(MyView *parentView);
        ~Panel();
        void addItem(QGraphicsItem *item);

    private:
        QList<QGraphicsItem*> _items;
        MyView *_view;
 };

#endif // PANEL_H
