#ifndef ASpriteManager_HPP
#define ASpriteManager_HPP

#include <QObject>

class Personnage;
class QTimer;
class ASpriteManager : public QObject
{
    Q_OBJECT

    public:
        ASpriteManager(Personnage *parent,  const QString& spritename, const short maxsprite);
        ~ASpriteManager();
        void razCpt();
        bool isRunning();
        /*
        stop and start is handled by parent's event "moveChanged"
        */
        virtual void init() = 0;

    protected:
        Personnage *_parent;
        const QString _spriteName;
        const QString _spritePath;
        const short _maxSprit;
        short _cpt;
        const short _timout;
        QTimer *_spriteTimer;
        QString _spriteFileName;

    protected slots:
        /**
         * Slot called on _spriteTimer timeout signal
         */
        void nextImg();
        void setSprite();
        void triggerRunning();
};

#endif // ASpriteManager_HPP
