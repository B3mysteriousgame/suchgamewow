#ifndef BALL_HPP
#define BALL_HPP

#include <QGraphicsItem>

class Mouse;
class GameManager;

class Patate;

class Ball : public QGraphicsItem
{
//    Q_OBJECT

    public:
        enum { Type = UserType + 6 };
        virtual int type() const{return Type;}

        Ball(qreal angl, QPointF po, QPointF origin, QGraphicsItem *parent = 0);
        Ball(const Ball& b);
        Ball(Patate *parent);
        QRectF boundingRect() const;
        QPainterPath shape() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *sogi,
                   QWidget *wid = 0);
        QPointF getCenter() const;
        void doEffect(QGraphicsItem *item);

    signals:

    public slots:

    private:
        void detectCollisions();
        void detectColls();
        QList<Mouse*> collidingMice(GameManager *gm);

    protected:
        void advance(int step);
        qreal _speed;
        qreal _diam;
        short _sens;
};

#endif // BALL_HPP
