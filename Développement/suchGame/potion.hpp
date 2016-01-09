#ifndef POTION_H
#define POTION_H

#include "item.hpp"

class Potion : public Item
{
    public:
        Potion(short val, Patate* owner);
        void DoAction();

    private:
        short _value;
        Patate* _owner;
};

#endif // POTION_H
