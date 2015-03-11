#ifndef MYVIEW_HPP
#define MYVIEW_HPP

#include <QGraphicsView>
#include <QPointF>

class MyView : public QGraphicsView
{
    Q_OBJECT
    public:
        explicit MyView();
        void keyPressEvent(QKeyEvent* event);
        void mousePressEvent(QMouseEvent *event);
        QPoint getCenter() const;
        QRectF getViewRect() const;

        static const qreal WIDTH = 467;
        static const qreal HEIGHT = 277;

    signals:

    public slots:

};

#endif // MYVIEW_HPP
