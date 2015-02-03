#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <QGraphicsScene>
#include "myview.hpp"
#include <QTimer>

class Mouse;
class Perso;
class Patate;

class GameManager : QObject
{
    Q_OBJECT

    public:
        static GameManager *Instance();
        void keyPressEvent(QKeyEvent* event);
        void mousePressEvent(QMouseEvent * event);

        QGraphicsScene* getScene() const ;
        MyView* getView() const;
        QTimer* getTimer() const;
        Perso* getPerso() const;
        QList<Mouse*> getSceneMice();
        QPointF getPersoPos() const;

        void addItemToScene(QGraphicsItem *item);
        void logCoords(const QGraphicsItem *item);
        void removeItem(QGraphicsItem *it);
        void setText(const QString& txt);
        void addItemToScene(QLineF &line);
        void addItemToScene(QRectF& rect);
        void addItemToScene(QGraphicsEllipseItem &el);
        int randInt(int low, int high) const;
        QPointF sceneCenter() const;

        void test();

    public slots:

    private:
        GameManager& operator= (const GameManager& g){}
        GameManager (const GameManager& g){}
        GameManager();
        ~GameManager();
        void avancerPerso();

        static GameManager *m_instance;

        QGraphicsScene *_scene;
        MyView *_view;
        QTimer *_timer;
        Perso *_perso;
        Patate *_patate;
        QGraphicsTextItem *_textItem;

};

#endif // GAMEMANAGER_HPP
