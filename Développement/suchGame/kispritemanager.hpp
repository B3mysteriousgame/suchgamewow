#ifndef KISPRITEMANAGER_HPP
#define KISPRITEMANAGER_HPP

#include <QObject>
#include "SpriteManager.hpp"
#include <QGraphicsPixmapItem>

class Patate;
class QTimer;
class KiSpriteManager : public ASpriteManager
{
    Q_OBJECT

    public:
        KiSpriteManager(Patate *parent,  const QString& spritename, const short maxsprite);
        void init();
        void stop();

    protected slots:
//        void triggerRunning();
        void triggerRunning(short isrunning = -1);
        void setSprite();
        void nextImg();

        protected:
        QGraphicsPixmapItem _kiAnim;
};

#endif // KISPRITEMANAGER_HPP
