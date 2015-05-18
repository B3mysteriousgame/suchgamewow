#include "longsword.h"

Longsword::Longsword()
{
  _pixmap = QPixmap(":images/Sprites/longsword.png");
   setPixmap(_pixmap);
  _atq = 70;
  _portee = 7;
  _def = 20;
  _nom = "Epee longue";
}

Longsword::~Longsword()
{

}

