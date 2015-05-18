#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include "arme.h"
#include "coffre.hpp"
#include "longsword.h"
#include "dragonsword.hpp"
#include <QDebug>

Coffre::Coffre():
    QObject()
{
    _isOpen = false;
    _popup = new Popup(this);
    _popup->setParentItem(this);
    _popup->moveBy(10,-15);
    _ouvrable = false;

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

void Coffre::advance(int phase)
{
     QLineF dist = QLineF(GameManager::Instance()->getPatatePos(),this->pos());
     if(dist.length() <=30 )
         _ouvrable = true;
     else
         _ouvrable = false;

     if(_ouvrable && !_isOpen)
        _popup->show();
     else
        _popup->hide();

}





