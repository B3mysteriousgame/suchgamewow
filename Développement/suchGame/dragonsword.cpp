#include "dragonsword.hpp"

Dragonsword::Dragonsword() :
    Arme()/*,
    _pixmap(QPixmap(":images/Sprites/dragonsword.png")),
    _nom("Epee de dragon de glace"),
    _atq(90),
    _portee(4),
    _def(5)*/
{
    _pixmap = QPixmap(":images/Sprites/dragonsword.png");
    _nom = "Epee de dragon de glace";
    setPixmap(_pixmap);
    _atq = 90;
    _portee = 4;
    _def = 5;
}

Dragonsword::~Dragonsword()
{

}

