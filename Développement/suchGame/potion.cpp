#include "potion.hpp"

Potion::Potion(short val, Patate *owner) :
    Item()
{
    _value = val;
    _owner = owner;
}

