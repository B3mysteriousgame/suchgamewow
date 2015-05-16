#include "dragonsword.hpp"

Dragonsword::Dragonsword()
{
    setPixmap(QPixmap(":images/Sprites/dragonsword.png"));
    _atq = 90;
    _portee = 4;
    _def = 5;
}

Dragonsword::~Dragonsword()
{

}

