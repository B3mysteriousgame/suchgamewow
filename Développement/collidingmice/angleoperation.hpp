#ifndef ANGLEOPERATION_HPP
#define ANGLEOPERATION_HPP

#include <QtGlobal>

class QPointF;

class AngleOperation
{
    public:
        static qreal normalizeAngle(qreal angle);
        static qreal degToRad(qreal angle);
        static qreal radToDeg(qreal angle);
        static QPointF addRelativeX(qreal addX, QPointF to, qreal havingDegAngle);
        static QPointF addRelativeY(qreal addY, QPointF to, qreal havingDegAngle);
        static QPointF addRelativeXY(qreal addX, qreal addY, QPointF to, qreal havingDegAngle);

        static const double Pi;
};

#endif // ANGLEOPERATION_HPP
