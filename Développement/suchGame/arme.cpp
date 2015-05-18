#include "arme.h"
#include "personnage.hpp"


Arme::Arme()
{

}

//int Arme::attaquer(Personnage *personnage)
//{
//    personnage->_actualhealth = personnage->_actualhealth - this->_atq;
//}
QPixmap Arme::get_pixmap()
{
    return _pixmap;
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

void Arme::set_nom(QString nom)
{
    _nom = nom;
}

QString Arme::get_nom()
{
    return _nom ;
}
