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
    /*
    QPointF p(25,25);
    int marginBetween = 15;
    const short largeur = 100, hauteur = 10;
    */

    _vie = new Barre(true);
    _mana = new Barre(true);
    _ki = new Barre(true);

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
    delete(_vie);
    delete(_mana);
    delete(_ki);
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
            //qWarning() << "dpos:" << dx << dy << dp;
            /*
            _vie->moveBy(dx, dy);
            _mana->moveBy(dx, dy);
            _ki->moveBy(dx, dy);
            */
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
