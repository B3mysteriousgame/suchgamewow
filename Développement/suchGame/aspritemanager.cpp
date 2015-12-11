#include "ASpriteManager.hpp"
#include "personnage.hpp"
#include "patate.hpp"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QTimer>

ASpriteManager::ASpriteManager(Personnage *parent,  const QString &spritename, const short maxsprite) :
    _parent(parent),
    _spriteName(spritename),
    _spritePath(":" + _spriteName + "/images/Sprites/" + _spriteName + "/" + _spriteName),
    _maxSprit(maxsprite),
    _cpt(0),
    _timout(130),
    _spriteTimer(new QTimer())
{}

//void ASpriteManager::init()
//{
//    qWarning() << "abs init";
// //    connect(_spriteTimer, SIGNAL(timeout()), this, SLOT(nextImg()));
// //    connect(_parent, SIGNAL(moveChanged()), this, SLOT(triggerRunning()));

// //    _spriteTimer->start(_timout);
//}

ASpriteManager::~ASpriteManager()
{
    _spriteTimer->stop();
    delete(_spriteTimer);
}

/**
 * @brief ASpriteManager::triggerRunning
 * Starts the timer if stopped, stops it otherwise
 */
void ASpriteManager::triggerRunning()
{
    static QString methodName = "ASpriteManager::triggerRunning";
    if(!_parent->isMovin())
    {
        _spriteTimer->stop();
        if(_parent->type() == Patate::Type)
            qWarning() << "sprite timer stop";
    }
    else
    {
        _spriteTimer->start(_timout);
        if(_parent->type() == Patate::Type)
            qWarning() << "sprite timer start";
    }
}

/**
 * @brief RaZ qd personnage change de sens
 */
void ASpriteManager::razCpt()
{
    _cpt = 0; // 0 car surement ++ avec le nextImg
}

bool ASpriteManager::isRunning()
{
    return _spriteTimer->isActive();
}

/*
void ASpriteManager::start()
{
    _spriteTimer->start(_timout);
    ing() << "ASpriteManager::start";
}

void ASpriteManager::stop()
{
    _spriteTimer->stop();
    //qwarning() << "ASpriteManager::stop";
}
*/

/**
 * Slot called on _spriteTimer timeout signal
 */
void ASpriteManager::nextImg()
{
    static bool parentJustStopped = true; // parce que parent est arrete a la creation

//    if(this->_spriteFileName == "kiAnim")
//    {
//        int i = 0;
//    }

    if(_parent->isMovin())
    {
        _cpt++;

        if(_cpt > _maxSprit)
            _cpt = 1;

        setSprite();
        parentJustStopped = true;
    }
    else // si ne bouge pas
    {
        if(parentJustStopped)
        {
            // on affiche la premiere image
            _cpt = 1;

            setSprite();
            parentJustStopped = false;
        }
    }
}

/**
 * @brief ASpriteManager::setSprite
 * Sets the parent's QPixmap with the current built path
 */
void ASpriteManager::setSprite()
{
    _spriteFileName = (_parent->getStrSens()).at(0) + QString::number(_cpt) + ".png";

    _parent->setPixmap(QPixmap(_spritePath + _spriteFileName));
}
