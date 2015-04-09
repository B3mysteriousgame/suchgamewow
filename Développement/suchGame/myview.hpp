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
        void keyReleaseEvent(QKeyEvent* event);
        void mousePressEvent(QMouseEvent *event);
        QPoint getCenter() const;
        QRectF getViewRect() const;

        static const qreal WIDTH = 900;
        static const qreal HEIGHT = 508;

    signals:

    public slots:

};

#endif // MYVIEW_HPP
