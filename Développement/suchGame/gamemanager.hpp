#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <QGraphicsScene>
#include "myview.hpp"
#include <QTimer>
#include <QGraphicsPixmapItem>

class Mouse;
class Perso;
class Patate;

class GameManager : QObject
{
    Q_OBJECT

    public:
        static GameManager *Instance();
        void keyPressEvent(QKeyEvent* event);
        void mousePressEvent(QMouseEvent *event);
        void scrollView(short sens);

        QGraphicsScene* getScene() const ;
        MyView* getView() const;
        QTimer* getTimer() const;
        Perso* getPerso() const;
        QList<Mouse*> getSceneMice();
        QPointF getPersoPos() const;

        void addItemToScene(QGraphicsItem *item);
        void logCoords(const QGraphicsItem *item);
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

    public slots:
        void popEnnemy();
        void removeItem(QGraphicsItem *it);
        void hideLvlUp();

    private:
        Q_DISABLE_COPY(GameManager)
        QGraphicsRectItem *rectangle;
        QGraphicsPixmapItem *_grass;
        QGraphicsPixmapItem *_background;

        //GameManager& operator= (const GameManager&){}
        //GameManager (const GameManager& g);
        GameManager();
        ~GameManager();
        void avancerPerso();
        void setPixmap(QPixmap);

        static GameManager *m_instance;

        QGraphicsScene *_scene;
        MyView *_view;
        QTimer *_timer;
        QTimer *_timerLvlUp;
        QTimer *_timerPopEnnemy;
        Perso *_perso;
        Patate *_patate;
        QGraphicsTextItem *_textItem;
        QGraphicsPixmapItem *_lvlUpTxt;
        int _ennemyCpt;

        void pauseItems();

};

#endif // GAMEMANAGER_HPP
