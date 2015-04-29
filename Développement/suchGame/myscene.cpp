#include "myscene.hpp"
#include <QPainter>
#include <QPixmap>
#include <QGraphicsScene>

MyScene::MyScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

void MyScene::drawBackground ( QPainter * painter, const QRectF & rect )
{
    QPixmap bckground(":/images/MapTest.png");
    painter->drawPixmap(rect, bckground, rect );
    QGraphicsScene::drawBackground(painter,rect);
}
