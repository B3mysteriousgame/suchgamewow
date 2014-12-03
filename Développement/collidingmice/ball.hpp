#ifndef BALL_HPP
#define BALL_HPP

#include <QGraphicsItem>

class Mouse;
class GameManager;

class Ball : public QGraphicsItem
{
//    Q_OBJECT

    public:
        enum { Type = UserType + 3 };

        Ball(qreal angl, QPointF po, QPointF origin, QGraphicsItem *parent = 0);
        Ball(const Ball& b);
        QRectF boundingRect() const;
        QPainterPath shape() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *sogi,
                   QWidget *wid = 0);
        QPointF center();

        virtual int type() const{return Type;}

    signals:

    public slots:

    private:
        void detectCollisions();
        void detectColls();
        QList<Mouse*> collidingMice(GameManager *gm);

    protected:
        void advance(int step);
        qreal speed;
        qreal diam;
        qreal width;
        qreal height;

        bool line;

};

#endif // BALL_HPP
