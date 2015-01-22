#include "ball.hpp"

#include <QPointF>
#include <QPainter>
#include <QStyleOption>
#include <QtDebug>
#include "math.h"
#include "gamemanager.hpp"
#include "angleoperation.hpp"
#include "perso.hpp"


Ball::Ball(qreal &angl, QPointF &ballScenePos, QPointF &origin, QGraphicsItem *parent) :
    QGraphicsItem(),
    speed(3),
    diam(20)
{
    setRotation( parent->rotation() );
    ballScenePos = AngleOperation::addRelativeXY(50, -9, ballScenePos, rotation());
    setPos( ballScenePos ); // pos en coord de scene !!

    //qWarning() << "ballScenePos:" << ballScenePos;
}

Ball::Ball(const Ball& b)
{

}

QRectF Ball::boundingRect() const
{
    float offset = 0.5;

    return QRectF(this->x()-offset, this->y()-offset, this->diam + 2. * offset, this->diam + 2. * offset);
}

QPainterPath Ball::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *sogi, QWidget *wid)
{
    painter->setBrush(Qt::green);
    painter->drawEllipse(0, 0, diam, diam);
}

void Ball::advance(int step)
{
}

///
/// \brief Retourne une liste d'objets Mouse en collision
/// \param Pointeur vers le gameManager pour eviter l'appelle d'instance()
/// \return Une QList des souris détectees
///
QList<Mouse*> Ball::collidingMice(GameManager *gm)
{
    QList<Mouse*> lmice = gm->getSceneMice();
    QList<Mouse*> lColMice = QList<Mouse*>();

    //for(int i = 0; i < max; ++i)
    foreach (Mouse *item, lColMice)
    {
        // tester si item est NULL
        if(collidesWithPath(item->shape()))
            lColMice.append(item);
    }

    return lColMice;
}

///
/// \brief Detecte les collision en utilisant Ball::collidingMice
///
void Ball::detectColls()
{
    static GameManager *gm = GameManager::Instance();
    bool touched = false;
    QList<Mouse*> lcolliding = collidingMice(gm);
    QString sentence = "";

    if(lcolliding.count() > 0)
    {
        foreach (Mouse *item, lcolliding)
        {
            switch(item->type())
            {
                /*
                case Perso::Type:
                    sentence = "PERSO";
                    break;
                */
                case Mouse::Type:
                    sentence = "MOUSE";
                    touched = true;
                    break;
                default:
                    sentence = "AUTRE :'(";
                    break;
            }
            qWarning() << sentence;
            if(touched)
                break;
        }
    }
}

///
/// \brief Detecte les collision en utilisant QGraphicsItem::collidingItems()
///
void Ball::detectCollisions()
{
    static bool touched = false;

    // detect collision
    static GameManager *gm = GameManager::Instance();
    QList<QGraphicsItem*> lcolliding = collidingItems();
    Perso *pitem = NULL;

    if(lcolliding.count() > 0)
    {
        foreach (QGraphicsItem* item, lcolliding)
        {
            qWarning() << "item, mouse, perso" << item->type() << "-" << Mouse::Type << "-" << Perso::Type;
            if( item->type() != Perso::Type && item->type() == Mouse::Type )
            {
                qWarning() << "MOUSE";

                gm->removeItem(item);
                touched = true;
                break;
            }
            else
                qWarning() << "NOT MOUSE ";
        }

    }
    //------- end detect collisions
}

QPointF Ball::getCenter() const
{
    QRectF boundR = boundingRect();
    return QPointF(boundR.x() + boundR.width() / 2,
                   boundR.y() + boundR.height() / 2);
}
