#ifndef SPRITEMANAGER_HPP
#define SPRITEMANAGER_HPP

#include <QObject>

class Personnage;
class QTimer;
class SpriteManager : public QObject
{
    Q_OBJECT

    public:
        SpriteManager(Personnage *parent,  const QString& spritename, const short maxsprite);
        ~SpriteManager();
        void razCpt();
        bool isRunning();
        /*
        void stop();
        void start();
        */

    private:
        QTimer *_spriteTimer;
        const short _maxSprit;
        const QString _spriteName;
        const QString _spritePath;
        QString _spriteFileName;
        Personnage *_parent;
        short _cpt;
        const short _timout;

    private slots:
        /**
         * Slot called on _spriteTimer timeout signal
         */
        void nextImg();
        void setSprite();
        void triggerRunning();
};

#endif // SPRITEMANAGER_HPP
