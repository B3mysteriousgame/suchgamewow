#include "myview.hpp"
#include <QDebug>
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

/**
 * @brief Returns view's center in scene's coordinate
 * @return
 */
QPoint MyView::getCenter() const
{
    return (mapToScene(QPoint(width() / 2, height() / 2))).toPoint();
}

/**
 * @brief Retourne le rectangle de la vue en coord de scene
 * @return
 */
QRectF MyView::getViewRect() const
{
    QPolygonF qpf = mapToScene( QRect(0, 0, width(), height()) );
    return qpf.boundingRect();
}
