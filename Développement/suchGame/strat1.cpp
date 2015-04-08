#include <QDebug>
#include "strat1.hpp"

Strat1::~Strat1()
{
    qWarning() << "Strat1 deleted.";
}

void Strat1::analyser ()
{
    qWarning() << "Strat1 analysed.";
}

void Strat1::appliquer ()
{
    qWarning() << "Strat1 applied.";



}
