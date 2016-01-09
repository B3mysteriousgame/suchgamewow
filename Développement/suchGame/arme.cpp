#include "arme.h"
#include "personnage.hpp"



Arme::Arme():
    Item(),
    _ramassable(false)
{
    _popup = new Popup(this);
    _popup->moveBy(10,-15);
}

Arme::~Arme()
{
    delete(_popup);
}

void Arme::advance(int /*phase*/)
{
    GameManager* const gm = GameManager::Instance();
    QLineF dist = QLineF(gm->getPatatePos(),this->pos());

    if(dist.length() <= 30 )
    {
        _ramassable = true;
        _popup->show();
        return; // du coup le reste fait comme un else
    }

    // else
    _ramassable = false;
    _popup->hide();
}

QPixmap Arme::get_pixmap() const
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

void Arme::set_atq(const int atq)
{
    _atq = atq;
}

void Arme::set_def(const int def)
{
    _def = def;
}

void Arme::set_portee(const int portee)
{
    _portee = portee;
}
