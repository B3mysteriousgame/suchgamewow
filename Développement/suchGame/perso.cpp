#include "perso.hpp"
#include "mouse.h"
#include "math.h"
#include "ball.hpp"
#include "gamemanager.hpp"
#include "angleoperation.hpp"
#include <QDebug>

Perso::Perso()
    : Mouse()
{
    color = QColor("yellow");
    angle = 90;
    speed = 1.5;
    balls = QList<Ball*>();

    setRotation(0);
    setPos(0, 0);
}

Perso::~Perso()
{
    foreach (Ball *b, balls)
    {
        delete(b);
    }
}

void Perso::avancer()
{
    //static float offset = 2.5 * speed;

    //setPos( AngleOperation::addRelativeX(offset, pos(), rotation()) );
    /*
    qreal x, y, c;
    QPointF pos = this->pos();

    c = AngleOperation::degToRad(angle);
    y = cos(c) * -1 * offset;
    x = sin(c) * offset;

    setPos(x + pos.x(), y + pos.y());
    */
}

void Perso::advance(int /*step*/){}

qreal Perso::getSpeed() const
{
    return speed;
}

QRectF Perso::boundingRect() const
{
    static qreal adjust = 0.5, height = 32, width = 59;

    QRectF rect = QRectF(x() - adjust, y() - adjust,
                         width + adjust * 2, height + adjust * 2);

    return rect;
}

QPainterPath Perso::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());

    return path;
}

QPointF Perso::getCenter() const
{
    return QPointF(boundingRect().x() + boundingRect().width() / 2,
                   boundingRect().y() + boundingRect().height() / 2 - 7);
}

QPointF Perso::getSceneCenter() const
{
    return mapToScene(getCenter());
}

void Perso::attaque()
{
    /*
    static GameManager *gm = GameManager::Instance();
    static QGraphicsScene *scene = gm->getScene();

    QPointF t1, ballPos;
    QLineF line;
    QList<QGraphicsItem*> items = scene->items();

    //t1 = center();
 //   scene->items()
    //line = QLineF(t1, ballPos);


    foreach(QGraphicsItem *qgi, items)
    {
        if(qgi->type() == Ball::Type)
            scene->removeItem(qgi);
    }

    Ball *b = new Ball(angle, scenePos(), sceneCenter(), this);

    gm->addItemToScene(b);
    */
}
