#include "kispritemanager.hpp"
#include "patate.hpp"
#include <QDebug>
#include <QTimer>

KiSpriteManager::KiSpriteManager(Patate *parent,  const QString &spritename, const short maxsprite) :
    ASpriteManager(parent, spritename, maxsprite)
{
    _timout = 110;
    this->init();
}

void KiSpriteManager::init()
{
    qWarning() << "ki init";

    _kiAnim.setPixmap(QPixmap(":kiAnim/images/Sprites/kiAnim/kiAnim1.png"));
    _kiAnim.setParentItem(_parent);
    _kiAnim.setPos( _parent->mapToScene(-30, -45) );
    _kiAnim.setFlag(QGraphicsItem::ItemStacksBehindParent);
    _kiAnim.setVisible(false);

    GameManager::Instance()->getScene()->addItem(&_kiAnim);

    connect(_spriteTimer, SIGNAL(timeout()), this, SLOT(nextImg()));
    connect(_parent, SIGNAL(kiChargeEvent(short)), this, SLOT(triggerRunning(short)));

    //_spriteTimer->start(_timout);
}

void KiSpriteManager::stop()
{
    _spriteTimer->stop();
    _kiAnim.setVisible(false);
}

/**
 * @brief ASpriteManager::triggerRunning
 * Starts the timer if stopped, stops it otherwise
 */
void KiSpriteManager::triggerRunning(short isrunning)
{
    //static QString methodName = "KiSpriteManager::triggerRunning";
    static QPoint offsetpoint(-30, -46);

    qWarning() << "trigger running" << _spritePath + _spriteFileName;
    if(isrunning == 0 || _spriteTimer->isActive())
    {
        qWarning() << "trigger running stop";
        _spriteTimer->stop();
        _kiAnim.setVisible(false);
    }
    else
    {
        qWarning() << "trigger running start";
        _spriteTimer->start(_timout);
        _kiAnim.setPos(_parent->pos() + offsetpoint);
        _kiAnim.setVisible(true);
    }
}

/**
 * @brief ASpriteManager::setSprite
 * Sets the parent's QPixmap with the current built path
 */
void KiSpriteManager::setSprite()
{
    _spriteFileName = QString::number(_cpt) + ".png";

    _kiAnim.setPixmap(QPixmap(_spritePath + _spriteFileName));
    //qWarning() << "setSprite:" << _spritePath + _spriteFileName;

}

/**
 * Slot called on _spriteTimer timeout signal
 */
void KiSpriteManager::nextImg()
{
//    static bool parentJustStopped = true; // parce que parent est arrete a la creation

    if( ((Patate*)_parent)->isCharginKi() )
    {
        _cpt++;

        if(_cpt > _maxSprit)
            _cpt = 1;

        setSprite();
//        parentJustStopped = true;
    }
    else // si ne charge pas
    {
//        if(parentJustStopped)
//        {
//            // on affiche la premiere image
//            _cpt = 1;

//            setSprite();
//            parentJustStopped = false;
//        }
    }
}
