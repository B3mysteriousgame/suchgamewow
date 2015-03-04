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

Ball::Ball(qreal angl, QPointF ballScenePos, QPointF origin, QGraphicsItem *parent) :
    QGraphicsItem(),
    _speed(6),
    _diam(50),
    _degats(50)
{
    setRotation( parent->rotation() );
    ballScenePos = AngleOperation::addRelativeXY(50, -9, ballScenePos, rotation());
    setPos( ballScenePos ); // pos en coord de scene !!

    //qWarning() << "ballScenePos:" << ballScenePos;
}

Ball::Ball(const Ball& b) :

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
    _diam(10),
    _degats(50)
{
    short offset = 10;
    qreal dx = 0, dy = 0;
    int angle = 0;

    if(parent != NULL)
    {
        setPos(parent->pos());
        //qWarning() << pos();

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
        //qWarning() << pos();
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

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *sogi, QWidget *wid)
{
    painter->setBrush(Qt::green);
    painter->drawEllipse(0, 0, _diam, _diam);
}

void Ball::advance(int step)
{
    static const qreal offset = 1, changeSensChance = 3;
    static const qreal maxX = GameManager::Instance()->getView()->width();
    static const qreal maxY = GameManager::Instance()->getView()->height();
    short newsens = -1;
    qreal dy = 0, dx = 0;

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

    // on verif qu'on est tj dans la scene
    if(x() > maxX || x() < 0 || y() > maxY || y() < 0)
        delete(this);

    // test collision
    QList<QGraphicsItem*> listCollides = collidingItems();
    if(listCollides.length() > 0)
        foreach (QGraphicsItem *item, listCollides)
            doEffect(item);
}

/**
 * @brief Retourne une liste d'objets Mouse en collision
 * @param Pointeur vers le gameManager pour eviter l'appelle d'instance()
 * @return Une QList des souris détectees
 */
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
            // qWarning() << "item, mouse, perso" << item->type() << "-" << Mouse::Type << "-" << Perso::Type;
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



void Ball::doEffect(QGraphicsItem *item)
{
    if(item->type() == Ennemy::Type)
    {
        Ennemy *leEnnemy = (Ennemy*) item;
        leEnnemy->loseHealth(_degats);
        qWarning() << "Ennemy touched" << leEnnemy->getActualHealth();

        if(leEnnemy->getActualHealth() <= 0)
        {
            qWarning() << "Ennemy killed";
            GameManager::Instance()->removeItem(leEnnemy);
        }
        delete(this);
    }
    else
        if(item->type() == Mouse::Type)
        {
            qWarning() << "got a mouse";
            GameManager::Instance()->removeItem(item);
            delete(this);
        }
}
