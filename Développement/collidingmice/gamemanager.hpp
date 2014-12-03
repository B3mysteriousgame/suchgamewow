#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <QGraphicsScene>
#include "myview.hpp"
#include <QTimer>

class Mouse;
class Perso;

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
        void addItemToScene(QGraphicsItem *item);
        void addItemToScene(QLineF line);
        void addItemToScene(QRectF rect);
        void setText(QString txt);
        void logCoords();
        QPointF persoPos();
        void removeItem(QGraphicsItem *it);
        Perso* getPerso();
        QList<Mouse*> getSceneMice();

    public slots:
        void changeColors();
        void changeColor(Mouse *m);

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
        QGraphicsTextItem *_textItem;

};

#endif // GAMEMANAGER_HPP
