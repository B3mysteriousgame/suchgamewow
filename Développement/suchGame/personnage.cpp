#include "personnage.hpp"
#include <QDebug>

int Personnage::getSens() const
{
    return _sens;
}

void Personnage::setSens(const short sens)
{

    if(sens != 0 && sens != 1 && sens != 2 && sens != 3 )
    {
        qDebug() << "Erreur valeur sens.";
        throw;
    }
    else
       this->_sens = sens;
}
