#ifndef SPRITEMANAGER_HPP
#define SPRITEMANAGER_HPP

#include <QObject>
#include "ASpriteManager.hpp"

class Personnage;
class QTimer;
class SpriteManager : public ASpriteManager
{
    Q_OBJECT

    public:
        SpriteManager(Personnage *parent,  const QString& spritename, const short maxsprite);
        void init();
};

#endif // SPRITEMANAGER_HPP
