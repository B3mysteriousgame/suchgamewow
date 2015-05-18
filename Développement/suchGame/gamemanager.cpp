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
#include "coffre.hpp"
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QFrame>

#ifdef Q_OS_WIN
#include <windows.h> // for Sleep
#endif
void GameManager::qSleep(int ms)
{
    if(ms <= 0)
        return;

#ifdef Q_OS_WIN
    Sleep(uint(ms));
#else
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
#endif
}


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
    _ennemyCpt = 0;
    _lvlUpTxt = NULL;
    _backgroundImgPath = ":/images/MapTest.png";

    _timer = new QTimer();
    _timerPopEnnemy = new QTimer();
    _timer = new QTimer();
    _timerLvlUp = new QTimer();

    _kiChargStartTimestamp = 0;
    _kiChargStopTimestamp = 0;
}

void GameManager::startGame()
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    initScene();


    // ajout de la frame avec les barres de stats
    _statsMan = new StatsManager(_scene);

    initView();


    _scene->setBackgroundBrush(QBrush(QPixmap(_backgroundImgPath)));
    //_scene->setSceneRect(0, 0, 1920, 1080);

//! [4]
    _view->setScene(_scene);
    _view->setRenderHint(QPainter::Antialiasing);
    //_view->setBackgroundBrush(QPixmap(":/images/MapTest.png"));
//! [4] //! [5]
    _view->setCacheMode(QGraphicsView::CacheBackground);
    _view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
//! [5] //! [6]

    _view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Colliding Mice"));
    _view->setAutoFillBackground(false);

    QSize qs(MyView::WIDTH, MyView::HEIGHT);
    _view->resize(qs);
    //_view->setFixedSize();

    //qWarning() << "Scene's at" << _scene->sceneRect().center();

    _view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    _view->show();

    // init connections
    QObject::connect(_timer, SIGNAL(timeout()), _scene, SLOT(advance()));
    QObject::connect(_timerPopEnnemy, SIGNAL(timeout()), this, SLOT(popEnnemy()));
    QObject::connect(_timerLvlUp, SIGNAL(timeout()), this, SLOT(hideLvlUp()));
    QObject::connect(_patate, SIGNAL(statChanged(const int, const QString&)), this, SLOT(setBarrePatate(const int, const QString&)));

    // start timers
    _timer->start(1000 / 33);
    _timerPopEnnemy->start(1000 * 5);

    //test coffre
        _coffre = new Coffre();
        _coffre->setActive(true);
        addItemToScene(_coffre);
        _coffre->setPos(150,150);

        // test inventaire
        _inventaire = new Inventaire();

        }
// test inventaire
void GameManager::AfficheInventaire()
{
        _inventaire->show();
        //_inventaire.setParent(_patate);
}


GameManager::~GameManager()
{
    delete(_scene);
    delete(_view);
    delete(_timer);
	delete(_timerPopEnnemy);
    delete(_patate);
    delete(_timerLvlUp);
    delete(_lvlUpTxt);
    delete(_grass);
    delete(_background);
    delete(_statsMan);
    GameManager::m_instance = NULL;
}


/**
 * @brief Removes an item from the scene and deletes it
 * @param it: the item to be removed
 **/
void GameManager::removeItem(QGraphicsItem *it)
{
    //_scene->removeItem(it);

    if(it->type() == Ennemy::Type)
        _ef.removeEnnemy((Ennemy*)it);

    if(it != NULL)
        delete(it);
}


Patate *GameManager::getPatate() const
{
    return _patate;
}

QGraphicsScene* GameManager::getScene() const
{
    return _scene;
}

MyView* GameManager::getView() const
{
    return _view;
}

QTimer* GameManager::getPopTimer() const
{
    return _timerPopEnnemy;
}

void GameManager::mousePressEvent(QMouseEvent*)
{
    //changeColor(_perso);
}

void GameManager::test()
{
    // _scene->setActivePanel(0);
    /*
    QFrame *testWidget = new QGraphicsWidget((QWidget)*_view);
    testWidget->setGeometry(QRect(10, 10, 400, 300));
    testWidget->setVisible(true);
    */
    qWarning() << "fram added";

}

void GameManager::keyPressEvent(QKeyEvent* event)
{
    if(_patate != NULL)
        switch (event->key())
        {
            case Qt::Key_Up:
                _patate->setSens(Patate::HAUT);
                _patate->setMovin(true);
                break;
            case Qt::Key_Down:
                _patate->setSens(Patate::BAS);
                _patate->setMovin(true);
                break;
            case Qt::Key_Left:
                _patate->setSens(Patate::GAUCHE);
                _patate->setMovin(true);
                break;
            case Qt::Key_Right:
                _patate->setSens(Patate::DROITE);
                _patate->setMovin(true);
                break;
            case Qt::Key_A :
                _patate->attaque();
                break;
            case Qt::Key_E :
                { // accolades sinn la declaration du ulong chie
                    ulong tt = event->timestamp();
                    if(tt - _kiChargStopTimestamp > 200)
                    {
                        _kiChargStartTimestamp = tt;

                        if(!_patate->isCharginKi())
                            _patate->setCharginKi(true);
                    }
                }
                break;
            case Qt::Key_R :
                _patate->quickPunch();
                break;
            case Qt::Key_F :
                _coffre->ouvrir();
                break;
            case Qt::Key_I :
                this->AfficheInventaire();
                break;
            case Qt::Key_Z :
                test();
                break;

            /*default:
                break;*/
        }
}

void GameManager::keyReleaseEvent(QKeyEvent* event)
{
    static short lastSensReleased = 0;

    if(_patate != NULL)
    {
        switch (event->key())
        {
            case Qt::Key_Up:
                lastSensReleased = Patate::HAUT;
                break;
            case Qt::Key_Down:
                lastSensReleased = Patate::BAS;
                break;
            case Qt::Key_Left:
                lastSensReleased = Patate::GAUCHE;
                break;
            case Qt::Key_Right:
                lastSensReleased = Patate::DROITE;
                break;
            case Qt::Key_E :
            /*
                { // accolades sinn la declaration du ulong chie
                    ulong tt = event->timestamp();
                    if(tt - _kiChargStartTimestamp > 200)
                    {
                        _kiChargStopTimestamp = tt;

                        if(_patate->isCharginKi())
                            emit chargeKiStopped();
                    }
                }
            */
                break;
            default:
                return;
        }
        if(_patate->getSens() == lastSensReleased)
            _patate->setMovin(false); // idle;
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

void GameManager::logCoords(const QGraphicsItem* /*item*/)
{
    QString coord("Pos: ");
    coord.append(QString().number(_perso->x()));
    coord.append(", ");
    coord.append(QString().number(_perso->y()));

    setText(coord);
    //qWarning() << "GameManager::logCoords --> Type:" << item->type() << "-" << coord;
}

void GameManager::addItemToScene(QRectF &rect)
{
    _scene->addRect(rect);
}

void GameManager::addItemToScene(QLineF &line)
{
    _scene->addLine(line);
}

void GameManager::addItemToScene(QGraphicsEllipseItem&)
{
    //_scene->addEllipse((new QGraphicsEllipseItem(el))->rect());
}

QPointF GameManager::getPatatePos() const
{
    return _patate->pos();
}

QList<Mouse*> GameManager::getSceneMice()
{
    QList<QGraphicsItem*> liste =  _scene->items();
    QList<Mouse*> listeM = QList<Mouse*>();
    //short max = liste.count();

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

/**
 * @brief Deplace la vue en fonction du sens passe en param,
 *  et met en pause les items qui ne sont plus visibles.
 *  Ne fait rien si mauvais sens
 * @param sens: indique le sens dans lequel scroller.
 *  Il doit correspondre à l'enum de Personnage (0 <= sens <= 3)
 */
void GameManager::scrollView(short sens)
{
    static qreal viewWidth = _view->width();
    static qreal viewHeight = _view->height();

    if(sens < 0 || sens > 3)
        return;

    QPointF point = _view->mapToScene(_view->getCenter());
    //QPointF oldPoint = point;

    pauseItems();

    switch(sens)
    {
        case Personnage::GAUCHE:
            point.rx() -= viewWidth;
            break;
        case Personnage::HAUT:
            point.ry() -= viewHeight;
            break;
        case Personnage::DROITE:
            point.rx() += viewWidth;
            break;
        case Personnage::BAS:
            point.ry() += viewHeight;
            break;
    }
    _view->centerOn(point);

    ////qWarning() << oldPoint << "-----------" << point;
}

void GameManager::ennemyGotKilled(const int xp)
{
    _patate->addXp(xp);
    _timerPopEnnemy->start(100 * randInt(1,50));

}


void GameManager::pauseItems()
{
    QRectF sceneRect(_view->mapToScene(0,0), _view->mapToScene(QPoint(_view->width(), _view->height())));

    ////qWarning() << sceneRect;
}

void GameManager::popEnnemy()
{
    _ef.createEnnemy();
}

void GameManager::patateLvlUp()
{
    // on affiche "level up"
    if(_lvlUpTxt == NULL)
    {
        _lvlUpTxt = new QGraphicsPixmapItem(QPixmap(":/images/Sprites/lvlUpTxt.png"));
        _lvlUpTxt->setParentItem(_patate);
        _scene->addItem(_lvlUpTxt);
        //qWarning() << "GameManager::patateLvlUp() txt added";
    }

    // on affiche le test
    _lvlUpTxt->setActive(true);
    _lvlUpTxt->show();
    _timerLvlUp->start(1000); // 1sec
}

void GameManager::hideLvlUp()
{
    _timerLvlUp->stop();
    _lvlUpTxt->hide();
    _lvlUpTxt->setActive(false);
}

//Gestion du timerPopEnnemy
bool GameManager::isTimerActive()
{
    return _timerPopEnnemy->isActive();
}

void GameManager::stopTimer()
{
    _timerPopEnnemy->stop();
}

void GameManager::startTimer(int ms)
{
    _timerPopEnnemy->start(ms);
}

void GameManager::centerOnPatate()
{
    QPointF dp = _view->getCenter();

    _view->centerOn(_patate);

    dp -= _view->getCenter();


    // deplacer barres
    _statsMan->moveBarresBy(dp);
}

void GameManager::setBarrePatate(const int pki, const QString &cible)
{
    _statsMan->setLargeur(pki, cible);

    _scene->update();
}

void GameManager::addMice()
{
    // Souris
    for (int i = 0; i < MouseCount; ++i)
    {
        Mouse *mouse = new Mouse();
        mouse->setPos(::sin((i * 6.28) / MouseCount) * 200 + (_scene->width() / 2),
                      ::cos((i * 6.28) / MouseCount) * 200 + (_scene->height() / 2));
        _scene->addItem(mouse);
    }
}

void GameManager::initScene()
{
    _scene = new QGraphicsScene();
    _patate = new Patate();

    _scene->setSceneRect(0, 0, 1920, 1200);
    _scene->setBackgroundBrush(QBrush(QPixmap(_backgroundImgPath)));
    _scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    _scene->addItem(_patate);
    addMice();
}

void GameManager::initView()
{
    _view = new MyView();

    _view->setScene(_scene);
    _view->setRenderHint(QPainter::Antialiasing);

    _view->setCacheMode(QGraphicsView::CacheBackground);
    _view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);


    _view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Colliding Mice"));
    _view->setAutoFillBackground(false);

    QSize qs(MyView::WIDTH, MyView::HEIGHT);
    _view->resize(qs);

    _view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    _view->show();
}

EnnemyFactory GameManager::getEnnemyFactory()
{
    return _ef;
}
