#ifndef MYVIEW_HPP
#define MYVIEW_HPP

#include <QGraphicsView>

class MyView : public QGraphicsView
{
    Q_OBJECT
    public:
        explicit MyView();
        void keyPressEvent(QKeyEvent* event);
        void mousePressEvent(QMouseEvent *event);

    signals:

    public slots:

};

#endif // MYVIEW_HPP
