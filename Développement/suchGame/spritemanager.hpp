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
//        ~SpriteManager();

//        void razCpt();
//        bool isRunning();

        /*
        stop and start is handled by parent's event "moveChanged"
        */
        void init();

//    private:
//        Personnage *_parent;
//        const QString _spriteName;
//        const QString _spritePath;
//        const short _maxSprit;
//        short _cpt;
//        const short _timout;
//        QTimer *_spriteTimer;
//        QString _spriteFileName;

//    private slots:
//        /**
//         * Slot called on _spriteTimer timeout signal
//         */
//        void nextImg();
//        void setSprite();
//        void triggerRunning();
};

#endif // SPRITEMANAGER_HPP
