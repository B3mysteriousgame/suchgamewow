#include <QDebug>
#include "strat2.hpp"

Strat2::~Strat2()
{
    qWarning() << "Strat2 deleted.";
}

void Strat2::analyser ()
{
    qWarning() << "Strat2 analysed.";
}

void Strat2::appliquer ()
{
    qWarning() << "Strat2 applied.";
}
