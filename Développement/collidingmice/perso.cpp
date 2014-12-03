#include "perso.hpp"
#include "mouse.h"
#include "math.h"
#include "ball.hpp"
#include "gamemanager.hpp"
#include "angleoperation.hpp"
#include <QDebug>

/*
static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

///
/// \brief normalize a radian Angle
/// \param angle
/// \return the normalized angle
///
static qreal AngleOperation::normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

static qreal AngleOperation::degToRad(qreal angle)
{
    return angle * Pi / 180.;
}

static qreal AngleOperation::radToDeg(qreal angle)
{
    return angle * 180 / Pi;
}
*/

Perso::Perso()
    : Mouse()
{
    color = QColor("yellow");
    angle = 90;
    speed = 1.5;
    balls = QList<Ball*>();

    setRotation(90);
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
    static float offset = 2.5 * speed;

    setPos( AngleOperation::addRelativeX(offset, pos(), rotation()) );
    /*
    qreal x, y, c;
    QPointF pos = this->pos();

    c = AngleOperation::degToRad(angle);
    y = cos(c) * -1 * offset;
    x = sin(c) * offset;

    setPos(x + pos.x(), y + pos.y());
    */
}

void Perso::advance(int step)
{
    /*
    QLineF lineToCenter(QPointF(0, 0), mapFromScene(0, 0));
    if (lineToCenter.length() > 150) {
        qreal angleToCenter = ::acos(lineToCenter.dx() / lineToCenter.length());
        if (lineToCenter.dy() < 0)
            angleToCenter = TwoPi - angleToCenter;
        angleToCenter = AngleOperation::normalizeAngle((Pi - angleToCenter) + Pi / 2);

        if (angleToCenter < Pi && angleToCenter > Pi / 4) {
            // Rotate left
            angle += (angle < -Pi / 2) ? 0.25 : -0.25;
        } else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
            // Rotate right
            angle += (angle < Pi / 2) ? 0.25 : -0.25;
        }
    } else if (::sin(angle) < 0) {
        angle += 0.25;
    } else if (::sin(angle) > 0) {
        angle -= 0.25;
//! [5] //! [6]
    }
//! [6]

    // Try not to crash with any other mice
//! [7]
    QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
                                                       << mapToScene(0, 0)
                                                       << mapToScene(-30, -50)
                                                       << mapToScene(30, -50));
    foreach (QGraphicsItem *item, dangerMice) {
        if (item == this)
            continue;

        QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
        qreal angleToMouse = ::acos(lineToMouse.dx() / lineToMouse.length());
        if (lineToMouse.dy() < 0)
            angleToMouse = TwoPi - angleToMouse;
        angleToMouse = AngleOperation::normalizeAngle((Pi - angleToMouse) + Pi / 2);

        if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
            // Rotate right
            angle += 0.5;
        } else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
            // Rotate left
            angle -= 0.5;
//! [7] //! [8]
        }
//! [8] //! [9]
    }
//! [9]

    // Add some random movement
//! [10]
    if (dangerMice.size() > 1 && (qrand() % 10) == 0) {
        if (qrand() % 1)
            angle += (qrand() % 100) / 500.0;
        else
            angle -= (qrand() % 100) / 500.0;
    }
//! [10]

//! [11]
    speed += (-50 + qrand() % 100) / 100.0;

    qreal dx = ::sin(angle) * 10;
    mouseEyeDirection = (qAbs(dx / 5) < 1) ? 0 : dx / 5;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(3 + sin(speed) * 3)));

    int i = 0;
    i += step;
    */
}

void Perso::addAngle(qreal a)
{
    angle = AngleOperation::radToDeg( AngleOperation::normalizeAngle(AngleOperation::degToRad( angle + a )) );
    setRotation(angle);
}

qreal Perso::getSpeed() const
{
    return speed;
}

QPointF Perso::center() const
{
    return QPointF(boundingRect().x() + boundingRect().width() / 2,
                   boundingRect().y() + boundingRect().height() / 2 - 7);
}

QPointF Perso::sceneCenter() const
{
    return mapToScene(center());
}

void Perso::attaque()
{
    static const int offset = 5, maxBalls = 2;
    QPointF t, t1, ballPos;
    QLineF line;
    int lol = 0;


    t = sceneCenter();
    t1 = center();
    ballPos = scenePos();


    line = QLineF(t1, ballPos);
    //GameManager::Instance()->addLineToScene(line);
    //qWarning() << "perso ballpos :" << ballPos;

    Ball *b = new Ball(angle, ballPos, t, this);
    //Ball *b1;

    GameManager::Instance()->addItemToScene(b);
}
