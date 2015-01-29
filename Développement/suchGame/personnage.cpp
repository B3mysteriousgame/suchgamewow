#include "personnage.hpp"

int Personnage::getSens() const
{
    return _sens;
}

void Personnage::setSens(const short sens)
{
    this->_sens = sens;
}
