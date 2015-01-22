#include "angleoperation.hpp"
#include <QPointF>
#include <math.h>


const double AngleOperation::Pi = 3.14159265358979323846264338327950288419717;

QPointF AngleOperation::addRelativeX(qreal addX, QPointF to, qreal havingDegAngle)
{
    if(addX == 0)
        return to;

    //QPointF newPos = QPointF();
    qreal x, y, c;

    c = degToRad(havingDegAngle);
    y = cos(c) * -1 * addX;
    x = sin(c) * addX;

    to.setX(x + to.x());
    to.setY(y + to.y());

    return to;
}

QPointF AngleOperation::addRelativeY(qreal addY, QPointF to, qreal havingDegAngle)
{
    if(addY == 0)
        return to;

    //QPointF newPos = QPointF();
    qreal x, y, c;

    c = degToRad(havingDegAngle);
    y = sin(c) * addY;
    x = cos(c) * addY;

    to.setX(x + to.x());
    to.setY(y + to.y());

    return to;
}

QPointF AngleOperation::addRelativeXY(qreal addX, qreal addY, QPointF to, qreal havingDegAngle)
{
    to = addRelativeX(addX, to, havingDegAngle);
    to = addRelativeY(addY, to, havingDegAngle);
    return to;
}

///
/// \brief normalize a radian Angle
/// \param angle
/// \return the normalized angle
///
qreal AngleOperation::normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += Pi * 2;
    while (angle > Pi * 2)
        angle -= Pi * 2;
    return angle;
}

qreal AngleOperation::degToRad(qreal angle)
{
    return angle * Pi / 180.;
}

qreal AngleOperation::radToDeg(qreal angle)
{
    return angle * 180 / Pi;
}
