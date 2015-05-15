#include "ball.hpp"

#include <QPointF>
#include <QPainter>
#include <QStyleOption>
#include <QtDebug>
#include "math.h"
#include "gamemanager.hpp"
#include "angleoperation.hpp"
#include "perso.hpp"
#include "patate.hpp"
#include "ennemy.hpp"

Ball::Ball(QPointF ballScenePos, QGraphicsItem *parent) :
    QGraphicsItem(),
    _speed(6),
    _diam(50)
{
    setRotation( parent->rotation() );
    ballScenePos = AngleOperation::addRelativeXY(50, -9, ballScenePos, rotation());
    setPos( ballScenePos ); // pos en coord de scene !!

    _degats = 5 + ((Personnage*)parent)->getAtk();

    ////qWarning() << "ballScenePos:" << ballScenePos;
}

Ball::Ball(const Ball&) :
    QGraphicsItem(),
    _speed(6),
    _diam(10),
    _degats(50)
{
      // TODO
}

Ball::Ball(Patate *parent) :
    QGraphicsItem(),
    _speed(6),
    _diam(10)
{
    _degats = 5 + parent->getAtk();

    short offset = 10;
    qreal dx = 0, dy = 0;
    int angle = 0;

    if(parent != NULL)
    {
        setPos(parent->pos());
        ////qWarning() << pos();

        _sens = parent->getSens();

        switch (_sens)
        {
            case Patate::HAUT:
                dy = -offset;
                angle = 0;
                break;
            case Patate::BAS:
                dy = offset;
                angle = 180;
                break;
            case Patate::GAUCHE:
                dx = -offset;
                angle = 270;
                break;
            case Patate::DROITE:
                dx = offset;
                angle = 90;
                break;
            default:
                break;
        }

        setRotation(angle);
        moveBy(dx, dy);
        ////qWarning() << pos();
    }
}

QRectF Ball::boundingRect() const
{
    float offset = 0.1;

    return QRectF(-offset, -offset, this->_diam + 2. * offset, this->_diam + 2. * offset);
}

int Ball::getDegats() const
{
    return _degats;
}

QPainterPath Ball::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setBrush(Qt::green);
    painter->drawEllipse(0, 0, _diam, _diam);
}

void Ball::advance(int /*step*/)
{
    static const qreal offset = 1;
    static GameManager* const gm = GameManager::Instance();
    static MyView* const view = gm->getView();
    //static QList<QGraphicsItem*> listCollides;
    static QRectF viewRect;

    QList<QGraphicsItem*> listCollides;


    //short newsens = -1;
    qreal dy = 0, dx = 0;

    viewRect = view->getViewRect();

    // test collision
    //listCollides.clear();
    listCollides = collidingEnnemy();
    if(listCollides.length() > 0)
    {
        doEffect(listCollides[0]);
        gm->removeItem(this);
    }
    else // nothing touched
    {
        switch (_sens)
        {
            case Patate::HAUT:
                dy = _speed * offset * -1;
                break;
            case Patate::BAS:
                dy = _speed * offset;
                break;
            case Patate::GAUCHE:
                dx = _speed * offset * -1;
                break;
            case Patate::DROITE:
                dx = _speed * offset;
                break;
            default:
                break;
        }
        moveBy(dx, dy);

        // on verif qu'on est tj dans la view
        if(x() > viewRect.bottomRight().x() || x() < viewRect.bottomLeft().x() || y() > viewRect.bottomRight().y() || y() < viewRect.topRight().y())
            delete(this);
    }
}

/**
 * @brief Retourne une liste d'objets Mouse ou Ennemy en collision
 * @return Une QList des souris/ennemy detectes
 */
QList<QGraphicsItem*> Ball::collidingEnnemy()
{
    QList<QGraphicsItem*> collidings = collidingItems();
    QList<QGraphicsItem*> collidingEnnemies;

    foreach (QGraphicsItem *qgi, collidings)
    {
        if(qgi->type() == Ennemy::Type || qgi->type() == Mouse::Type)
            collidingEnnemies.append(qgi);
    }

    return collidingEnnemies;
}

QPointF Ball::getCenter() const
{
    QRectF boundR = boundingRect();
    return QPointF(boundR.x() + boundR.width() / 2,
                   boundR.y() + boundR.height() / 2);
}



void Ball::doEffect(QGraphicsItem *item)
{
    static GameManager* const gm = GameManager::Instance();
    if(item->type() == Ennemy::Type)
    {
        Ennemy *leEnnemy = (Ennemy*) item;
        if(leEnnemy->isTargetable())
            leEnnemy->loseHealth(_degats);
        //qWarning() << "Ennemy touched" << leEnnemy->getActualHealth();

        if(leEnnemy->getActualHealth() <= 0) // si mort
        {
            //qWarning() << "Ennemy killed";
            gm->ennemyGotKilled(leEnnemy->getXpDon());
            gm->removeItem(leEnnemy);
        }
        //delete(this);
    }
    else
        if(item->type() == Mouse::Type)
        {
            GameManager::Instance()->removeItem(item);
            //delete(this);
        }
}
