#include "gamemanager.hpp"
#include <QObject>
#include "mouse.h"
#include "perso.hpp"
#include "patate.hpp"
#include <QtWidgets>
#include <QGraphicsTextItem>
#include <math.h>

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
    _perso = new Perso();

    _timer = new QTimer();

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
//! [0]

//! [1]
    _scene->setSceneRect(-300, -300, 600, 600);
//! [1] //! [2]
    _scene->setItemIndexMethod(QGraphicsScene::NoIndex);
//! [2]

//! [3]
    // Souris
    for (int i = 0; i < MouseCount; ++i)
    {
        Mouse *mouse = new Mouse();
        mouse->setPos(::sin((i * 6.28) / MouseCount) * 200,
                      ::cos((i * 6.28) / MouseCount) * 200);
        _scene->addItem(mouse);
    }
    /*Mouse *mouse = new Mouse();
    mouse->setPos(100,0);
    _scene->addItem(mouse);*/

    _scene->addItem(_perso);
//! [3]
    _scene->addRect(_perso->boundingRect());
    //_scene->addRect(mouse->boundingRect());

    _textItem = _scene->addText("lol");

    _textItem->setPlainText("lol");
    _textItem->setPos(-300, -300);
    logCoords();



    // repere
    /*
    _scene->addLine(QLine(QPoint(0,-300), QPoint(0,300)));
    _scene->addLine(QLine(QPoint(-300, 0), QPoint(300, 0)));
    */

    // Patate
    _scene->addItem(new Patate(":/images/patate.png"));

//! [4]
    _view->setScene(_scene);
    _view->setRenderHint(QPainter::Antialiasing);
    _view->setBackgroundBrush(QPixmap(":/images/cheese.jpg"));
//! [4] //! [5]
    _view->setCacheMode(QGraphicsView::CacheBackground);
    _view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    _view->setDragMode(QGraphicsView::ScrollHandDrag);
//! [5] //! [6]
    _view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Colliding Mice"));
    _view->resize(700, 700);
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
    delete(_perso);
    GameManager::m_instance = NULL;
}

void GameManager::changeColors()
{
    QList<QGraphicsItem*> l = _scene->items();
    foreach (QGraphicsItem* qgi, l)
    {
        qgi = (Mouse*)qgi;
        if((Mouse*)qgi != NULL)
            ((Mouse*)qgi)->SetColor();
    }
}

///
/// \brief Removes an item from the scene and deletes it
/// \param it: the item to be removed
///
void GameManager::removeItem(QGraphicsItem *it)
{
    _scene->removeItem(it);
    delete(it);
}

Perso* GameManager::getPerso()
{
    return _perso;
}

void GameManager::changeColor( Mouse *m)
{
    m->SetColor();
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
    changeColor(_perso);
}

void GameManager::test()
{
    QPointF p = _perso->pos();
    QGraphicsEllipseItem *e = _scene->addEllipse(_perso->boundingRect());
    e->show();
    e->setRotation( _perso->rotation() - 90 );
    qWarning() << p.x() << "/" << p.y() << " - " << e->rotation();
}

void GameManager::keyPressEvent(QKeyEvent* event)
{
    static short angleOffset = 5;

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
}

void GameManager::addItemToScene(QGraphicsItem *item)
{
    _scene->addItem(item);
}

void GameManager::setText(QString txt)
{
    _textItem->setPlainText(txt);
}

void GameManager::avancerPerso()
{
    _perso->avancer();

    logCoords();
}

void GameManager::logCoords()
{
    QPointF centre =  _perso->sceneCenter();
    QString coord("Pos: ");
    coord.append(QString().number(_perso->x()));
    coord.append(", ");
    coord.append(QString().number(_perso->y()));

    coord.append("; Centre: ");
    coord.append(QString().number(centre.x()));
    coord.append(", ");
    coord.append(QString().number(centre.y()));

    setText(coord);
    //return coord;
}

void GameManager::addItemToScene(QRectF rect)
{
    _scene->addRect(rect);
}

void GameManager::addItemToScene(QLineF line)
{
    _scene->addLine(line);
}

QPointF GameManager::persoPos()
{
    return _perso->sceneCenter();
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
