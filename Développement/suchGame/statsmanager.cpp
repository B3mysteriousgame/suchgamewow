#include "statsmanager.hpp"
#include "myview.hpp"
#include "highlighteffect.hpp"
#include "gamemanager.hpp"
#include <QGraphicsScene>
#include <QDebug>

StatsManager::StatsManager(QGraphicsScene *scene)
{
    QPointF p(25,25);
    const int marginBetween = 15;
    Barre *joeBarre;

    _barreDico.insert("vie", new Barre(true));
    _barreDico.insert("mana", new Barre(true));
    _barreDico.insert("ki", new Barre(true));

    joeBarre = _barreDico["vie"];
    joeBarre->setColor(QColor(Qt::red));
    joeBarre->setPos(p);

    p.ry() += marginBetween;


    joeBarre = _barreDico["mana"];
    joeBarre->setColor(QColor(Qt::blue));
    joeBarre->setPos(p);

    p.ry() += marginBetween;


    joeBarre = _barreDico["ki"];
    joeBarre->setColor(QColor(255, 137, 0));
    joeBarre->setPos(p);

    initBarres(scene);
}

StatsManager::~StatsManager()
{
    GameManager *gm = GameManager::Instance();
    /*
    short size = _barreDico.size();

    for(int i = 0; i < size; ++i)
    {
        gm->removeItem(_barreDico.);
    }
    */
    Barre *toRemove = NULL;
    QList<QString> keys = _barreDico.keys();
    foreach (QString s, keys)
    {
        toRemove = _barreDico.take(s);
        gm->removeItem(toRemove);
    }
}

void StatsManager::moveBarresBy(const QPointF &dp)
{
    static bool firstTime = true;
    qreal dx, dy;

    dx = dp.x() * -1;
    dy = dp.y() * -1;

    if(firstTime)
        firstTime = false;
    else
    {
        if(dx != 0 || dy != 0)
        {
            for(QHash<QString, Barre*>::iterator i = _barreDico.begin(); i != _barreDico.end(); ++i)
                (i.value())->moveBy(dx, dy);
        }
    }
}

void StatsManager::setLargeur(const int largeur, const QString &cible)
{
    Barre *joebar = _barreDico[cible];

    joebar->setLargeur(largeur);
    //joebar->s
}

void StatsManager::initBarres(QGraphicsScene *scene)
{
    const short largeur = 100, hauteur = 10;

    for(QHash<QString, Barre*>::iterator i = _barreDico.begin(); i != _barreDico.end(); ++i)
    {
        Barre *b = i.value();
        b->setHauteur(hauteur);
        b->setLargeur(largeur);
        b->setZValue(20000);
        b->setGraphicsEffect(new HighlightEffect(0.5, b));

        scene->addItem(b);
    }

}
