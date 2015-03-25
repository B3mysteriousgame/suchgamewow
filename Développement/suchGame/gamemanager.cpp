#include "gamemanager.hpp"
#include <QObject>
#include "mouse.h"
#include "perso.hpp"
#include "patate.hpp"
#include <QtWidgets>
#include <QGraphicsTextItem>
#include <math.h>
#include "ennemy.hpp"
#include "barre.hpp"
#include <iostream>

static const double Pi = 3.14159265358979323846264338327950288419717;
static const int MouseCount = 7;
GameManager* GameManager::m_instance = NULL;

GameManager* GameManager::Instance()
{
    if(m_instance == NULL)
        m_instance = new GameManager();

    return m_instance;
}

GameManager::GameManager()
    :QObject()
{
    _view = new MyView();
    _scene = new QGraphicsScene();
    //_perso = new Perso();
    _perso = NULL;
    _patate = new Patate();

    _timer = new QTimer();

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
//! [0]

//! [1]
    _scene->setSceneRect(0, 0, 936, 555);
//! [1] //! [2]
    _scene->setItemIndexMethod(QGraphicsScene::NoIndex);
//! [2]

//! [3]
    // Souris
    for (int i = 0; i < MouseCount; ++i)
    {
        Mouse *mouse = new Mouse();
        mouse->setPos(::sin((i * 6.28) / MouseCount) * 200 + (_scene->width() / 2),
                      ::cos((i * 6.28) / MouseCount) * 200 + (_scene->height() / 2));
        _scene->addItem(mouse);
    }

    //Test ajout ennemy
        Ennemy *ennemy = new Ennemy();
        ennemy->setPos(::sin((1 * 6.28) / MouseCount) * 200,
                       ::cos((1 * 6.28) / MouseCount) * 200);
        Barre *barre = ennemy->getBarre();
        barre->moveBy(-12,-15);
        barre->setParentItem(ennemy);

       _scene->addItem(ennemy);
       _scene->addItem(barre);

     // Test ajout barre sur ennemy
//       QGraphicsItem *barre = new QGraphicsRectItem(0,0,50,10);
//       barre->moveBy(-12,-15);
//       barre->setParentItem(ennemy);
//       _scene->addItem(barre);

       _textItem = _scene->addText("Je suis un vilain ennemy");
       _textItem->setParentItem(ennemy);
       _textItem->setPlainText("Je suis un vilain ennemy");


    /*Mouse *mouse = new Mouse();
    mouse->setPos(100,0);
    _scene->addItem(mouse);*/

    //_scene->addItem(_perso);
    _scene->addItem(_patate);
//! [3]
    //_scene->addRect(_perso->boundingRect());
    //_scene->addRect(mouse->boundingRect());

    _textItem = _scene->addText("lol");

    _textItem->setPlainText("lol");
    _textItem->setPos(-300, -300);
    //logCoords();



    // repere
    /*
    _scene->addLine(QLine(QPoint(0,-300), QPoint(0,300)));
    _scene->addLine(QLine(QPoint(-300, 0), QPoint(300, 0)));
    */

    // Patate
    //_scene->addItem(new Patate());

//! [4]
    _view->setScene(_scene);
    _view->setRenderHint(QPainter::Antialiasing);
    _view->setBackgroundBrush(QPixmap(":/images/map.png"));
//! [4] //! [5]
    _view->setCacheMode(QGraphicsView::CacheBackground);
    _view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //_view->setDragMode(QGraphicsView::ScrollHandDrag);
//! [5] //! [6]

    _view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Colliding Mice"));
    _view->setAutoFillBackground(false);

    QSize qs(936, 555);
    _view->resize(qs);
    //_view->setFixedSize();

    _view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    _view->show();


    QObject::connect(_timer, SIGNAL(timeout()), _scene, SLOT(advance()));
    //QObject::connect(_scene, SIGNAL(keyPressEvent()), this, SLOT(changeColors()));


    _timer->start(1000 / 33);
}

GameManager::~GameManager()
{
    delete(_scene);
    delete(_view);
    delete(_timer);
    //delete(_perso);
    delete(_patate);
    GameManager::m_instance = NULL;
}


/**
 * @brief Removes an item from the scene and deletes it
 * @param it: the item to be removed
 **/
void GameManager::removeItem(QGraphicsItem *it)
{
    _scene->removeItem(it);
    delete(it);
}

Perso* GameManager::getPerso() const
{
    return _perso;
}

QGraphicsScene* GameManager::getScene() const
{
    return _scene;
}

MyView* GameManager::getView() const
{
    return _view;
}

QTimer* GameManager::getTimer() const
{
    return _timer;
}

void GameManager::mousePressEvent(QMouseEvent *event)
{
    //changeColor(_perso);
}

void GameManager::test()
{
   Patate jose = Patate();
   Ennemy manuel = Ennemy();
   //jose.attaque(manuel);
   qWarning() << "Manuel a:" << QString().number(manuel.getActualHealth()) << "pv";


    //qWarning() << p.x() << "/" << p.y() << " - " << e->rotation();
}

void GameManager::keyPressEvent(QKeyEvent* event)
{
    static short angleOffset = 5;
    /*
    if(_perso != NULL)
        switch (event->key())
        {
            case Qt::Key_Up:
                avancerPerso();
                break;
            case Qt::Key_Left:
                _perso->addAngle(-1 * angleOffset * _perso->getSpeed());
                break;
            case Qt::Key_Right:
                _perso->addAngle(angleOffset * _perso->getSpeed());
                break;
            case Qt::Key_A:
                _perso->attaque();
                break;
            case Qt::Key_Z:
                test();
                break;
            default:
                break;
        }
    */
    if(_patate != NULL)
        switch (event->key())
        {
            case Qt::Key_Up:
                // _patate->setSens(Patate::HAUT);
                _patate->avancer(Patate::HAUT);
                break;
            case Qt::Key_Down:
                // _patate->setSens(Patate::BAS);
                _patate->avancer(Patate::BAS);
                break;
            case Qt::Key_Left:
                // _patate->setSens(Patate::GAUCHE);
                _patate->avancer(Patate::GAUCHE);
                break;
            case Qt::Key_Right:
                // _patate->setSens(Patate::DROITE);
                _patate->avancer(Patate::DROITE);
                break;
            case Qt::Key_A :
                _patate->attaque();
                break;
            default:
                break;
        }
}

void GameManager::addItemToScene(QGraphicsItem *item)
{
    _scene->addItem(item);
}

void GameManager::setText(const QString &txt)
{
    _textItem->setPlainText(txt);
}

void GameManager::avancerPerso()
{
    _perso->avancer();

    //logCoords();
}

void GameManager::logCoords(const QGraphicsItem *item)
{
    QString coord("Pos: ");
    coord.append(QString().number(_perso->x()));
    coord.append(", ");
    coord.append(QString().number(_perso->y()));

    setText(coord);
    qWarning() << "GameManager::logCoords --> Type:" << item->type() << "-" << coord;
}

void GameManager::addItemToScene(QRectF &rect)
{
    _scene->addRect(rect);
}

void GameManager::addItemToScene(QLineF &line)
{
    _scene->addLine(line);
}

void GameManager::addItemToScene(QGraphicsEllipseItem& el)
{
    //_scene->addEllipse((new QGraphicsEllipseItem(el))->rect());
}

QPointF GameManager::getPersoPos() const
{
    return _perso->pos();
}

QList<Mouse*> GameManager::getSceneMice()
{
    QList<QGraphicsItem*> liste =  _scene->items();
    QList<Mouse*> listeM = QList<Mouse*>();
    short max = liste.count();

    foreach (QGraphicsItem* item, liste)
    {
        if(item->type() == Mouse::Type)
            listeM.append( (Mouse*)item );
    }

    return listeM;
}

int GameManager::randInt(int low, int high) const
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

QPointF GameManager::sceneCenter() const
{
    return QPointF(_scene->width() / 2, _scene->height() / 2);
}
