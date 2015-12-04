#include "spritemanager.hpp"
#include "personnage.hpp"
#include <QDebug>
#include <QTimer>

SpriteManager::SpriteManager(Personnage *parent,  const QString &spritename, const short maxsprite) :
//    _parent(parent),
//    _spriteName(spritename),
//    _spritePath(":" + _spriteName + "/images/Sprites/" + _spriteName + "/" + _spriteName),
//    _maxSprit(maxsprite),
//    _cpt(0),
//    _timout(130),
//    _spriteTimer(new QTimer())
    ASpriteManager(parent, spritename, maxsprite)
{
    this->init();
}

void SpriteManager::init()
{
    qWarning() << "concr init";
    connect(_spriteTimer, SIGNAL(timeout()), this, SLOT(nextImg()));
    connect(_parent, SIGNAL(moveChanged()), this, SLOT(triggerRunning()));

    _spriteTimer->start(_timout);
}

//SpriteManager::~SpriteManager()
//{
//    _spriteTimer->stop();
//    delete(_spriteTimer);
//}

/**
 * @brief SpriteManager::triggerRunning
 * Starts the timer if stopped, stops it otherwise
 */
//void SpriteManager::triggerRunning()
//{
//    static QString methodName = "SpriteManager::triggerRunning";
//    if(_spriteTimer->isActive())
//    {
//        _spriteTimer->stop();
//    }
//    else
//    {
//        _spriteTimer->start(_timout);
//    }
//}

///**
// * @brief RaZ qd personnage change de sens
// */
//void SpriteManager::razCpt()
//{
//    _cpt = 0; // 0 car surement ++ avec le nextImg
//}

//bool SpriteManager::isRunning()
//{
//    return _spriteTimer->isActive();
//}

///*
//void SpriteManager::start()
//{
//    _spriteTimer->start(_timout);
//    ing() << "SpriteManager::start";
//}

//void SpriteManager::stop()
//{
//    _spriteTimer->stop();
//    //qwarning() << "SpriteManager::stop";
//}
//*/

///**
// * Slot called on _spriteTimer timeout signal
// */
//void SpriteManager::nextImg()
//{
//    static bool parentJustStopped = true; // parce que parent est arrete a la creation

//    if(_parent->isMovin())
//    {
//        _cpt++;

//        if(_cpt > _maxSprit)
//            _cpt = 1;

//        setSprite();
//        parentJustStopped = true;
//    }
//    else // si ne bouge pas
//    {
//        if(parentJustStopped)
//        {
//            // on affiche la premiere image
//            _cpt = 1;

//            setSprite();
//            parentJustStopped = false;
//        }
//    }
//}

///**
// * @brief SpriteManager::setSprite
// * Sets the parent's QPixmap with the current built path
// */
//void SpriteManager::setSprite()
//{
//    _spriteFileName = (_parent->getStrSens()).at(0) + QString::number(_cpt) + ".png";

//    _parent->setPixmap(QPixmap(_spritePath + _spriteFileName));
//}
