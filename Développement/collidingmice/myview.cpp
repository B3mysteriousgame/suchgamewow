#include "myview.hpp"
#include "gamemanager.hpp"

MyView::MyView() :
    QGraphicsView()
{
}

void MyView::keyPressEvent(QKeyEvent* event)
{
    GameManager *g = GameManager::Instance();
    g->keyPressEvent(event);
}

void MyView::mousePressEvent(QMouseEvent *event)
{
    GameManager::Instance()->mousePressEvent(event);
}
