#include "arme.h"

Arme::Arme()
{

}

int Arme::get_atq() const
{
    return _atq;
}

int Arme::get_def() const
{
    return _def;
}

int Arme::get_portee() const
{
    return _portee;
}

void Arme::set_atq(int atq)
{
    _atq = atq;
}

void Arme::set_def(int def)
{
    _def = def;
}

void Arme::set_portee(int portee)
{
    _portee = portee;
}
