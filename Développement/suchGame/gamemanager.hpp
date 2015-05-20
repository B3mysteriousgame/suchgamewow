#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <QGraphicsScene>
#include "myview.hpp"
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QtGlobal>
#include "ennemyfactory.h"
#include "statsmanager.hpp"
//#include "inventaire.hpp"


class Mouse;
class Perso;
class Patate;
class Ennemy;
class Coffre;
class Obstacle;

class GameManager : public QObject
{
    Q_OBJECT
    public:
        static GameManager *Instance();
        void keyPressEvent(QKeyEvent* event);
        void keyReleaseEvent(QKeyEvent* event);
        void mousePressEvent(QMouseEvent *event);
        void scrollView(short sens);

        QGraphicsScene* getScene() const ;
        MyView* getView() const;
        Patate* getPatate() const;
        QList<Mouse*> getSceneMice();
        QPointF getPatatePos() const;
        EnnemyFactory* getEnnemyFactory();

        void addItemToScene(QGraphicsItem *item);
        void logCoords(const QGraphicsItem*);
        void setText(const QString& txt);
        void addItemToScene(QLineF &line);
        void addItemToScene(QRectF& rect);
        void addItemToScene(QGraphicsEllipseItem &el);
        int randInt(int low, int high) const;
        QPointF sceneCenter() const;
        void ennemyGotKilled(const int xp);
        static void qSleep(int ms);
        void test();
        void patateLvlUp();
        void centerOnPatate();
        void startGame();
        void stopGame();
        void AfficheInventaire();
        void stopEnnemys();

    signals:
        void downSignal();
        void rightSignal();
        void leftSignal();
        void upSignal();
        void stopMovinSignal();
        void chargeKiStarted();
        void chargeKiStopped();

    public slots:
        void removeItem(QGraphicsItem *it);
        void hideLvlUp();

   private slots:
        void setBarrePatate(const int pki, const QString &cible);
        void potatoDead();

    private:
        Q_DISABLE_COPY(GameManager)
        QGraphicsRectItem *rectangle;
        QGraphicsPixmapItem *_grass;
        QGraphicsPixmapItem *_background;
        QString _backgroundImgPath;

        //GameManager& operator= (const GameManager&){}
        //GameManager (const GameManager& g);
        GameManager();
        ~GameManager();
        void avancerPerso();
        void setPixmap(QPixmap);
        void addMice();
        void initScene();
        void initView();

        static GameManager *m_instance;

        QGraphicsScene *_scene;
        MyView *_view;
        QTimer *_timerAdvance;
        QTimer *_timerLvlUp;
        EnnemyFactory _ef;
        Coffre *_coffre;
<<<<<<< HEAD
        Inventaire *_inventaire;
        Obstacle *_obstacle;
=======
>>>>>>> f3490ced2335cdd961ebf815cf82d3179c30574a


        Perso *_perso;
        Patate *_patate;
        QGraphicsTextItem *_textItem;
        QGraphicsPixmapItem *_lvlUpTxt;
        int _ennemyCpt;
        StatsManager *_statsMan;
        ulong _kiChargStartTimestamp;
        ulong _kiChargStopTimestamp;

        void pauseItems();
        void pauseItems1();

};

#endif // GAMEMANAGER_HPP
