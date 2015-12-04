#include "spritemanager.hpp"
#include "personnage.hpp"
#include <QDebug>
#include <QTimer>

SpriteManager::SpriteManager(Personnage *parent,  const QString &spritename, const short maxsprite) :
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
