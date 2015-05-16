#include "longsword.h"

Longsword::Longsword()
{
  setPixmap(QPixmap(":images/Sprites/longsword.png"));
  _atq = 70;
  _portee = 7;
  _def = 20;
}

Longsword::~Longsword()
{

}

