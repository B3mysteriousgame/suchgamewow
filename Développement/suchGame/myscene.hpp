#ifndef MYSCENE_HPP
#define MYSCENE_HPP

#include <QGraphicsScene>

class MyScene : public QGraphicsScene
{
    Q_OBJECT

    public:
        explicit MyScene(QObject *parent = 0);
        void drawBackground ( QPainter * painter, const QRectF & rect );

signals:

public slots:

};

#endif // MYSCENE_HPP
