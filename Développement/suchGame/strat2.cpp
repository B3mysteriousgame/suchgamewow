#include <QDebug>
#include "strat2.hpp"
#include "gamemanager.hpp"
#include "patate.hpp"
#include "barre.hpp"
#include <QLineF>

Strat2::Strat2(Ennemy *parent, QPointF dest)
{
    _parent = parent;
    _dest = dest;
    _clocheproche = false;
}

Strat2::~Strat2()
{
    //qWarning() << "Strat2 deleted.";
}

void Strat2::analyser ()
{
    QLineF ligne = QLineF(_dest,_parent->pos());
    if(ligne.length() <= 5)
    {
        _clocheproche = true;
    }
    else
        _clocheproche = false;
}

void Strat2::appliquer ()
{
    if(_clocheproche)
    {
        //taper la cloche

    }
    else
    {
        _parent->MoveToDest(_dest);
        _parent->MoveToDest(_dest);
        _parent->MoveToDest(_dest);
    }

}
