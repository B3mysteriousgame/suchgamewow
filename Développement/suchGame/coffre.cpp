#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include "arme.h"
#include "coffre.hpp"
#include "longsword.h"
#include "dragonsword.hpp"
#include <QDebug>

Coffre::Coffre()
{
    _isOpen = false;

    int alea = GameManager::Instance()->randInt(1,2);
    if(alea == 1)
        _arme = new Longsword();
    else
        _arme = new Dragonsword();
    setPixmap(QPixmap(":/images/Sprites/coffre.png"));
}

Coffre::~Coffre()
{

}

void Coffre::ouvrir()
{
    QLineF dist = QLineF(GameManager::Instance()->getPatatePos(),this->pos());
    if( dist.length() <= 30 )
    {
        _isOpen = true;
        GameManager::Instance()->addItemToScene(_arme);
        _arme->setPos(this->pos().x() + 50,this->pos().y());
    }

    qWarning() << "chips" << this->_isOpen;

}



