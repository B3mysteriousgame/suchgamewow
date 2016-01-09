#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QDebug>

#include "item.hpp"
#include "coffre.hpp"
#include "longsword.h"
#include "dragonsword.hpp"
#include "gamemanager.hpp"
#include "popup.hpp"
#include "arme.h"


Coffre::Coffre():
    QObject(),
    _isOpen(false),
    _ouvrable(false),
    _popup(new Popup(this))
{
    _popup->setParentItem(this);
    _popup->moveBy(10,-15);

    int alea = GameManager::Instance()->randInt(1,2);
    if(alea == 1)
       _item = new Longsword();
    else
       _item = new Dragonsword();

    setPixmap(QPixmap(":/images/Sprites/coffre.png"));
}

Coffre::~Coffre()
{
    delete(_popup);
}

bool Coffre::ouvrir()
{
    QLineF dist = QLineF(GameManager::Instance()->getPatatePos(),this->pos());
    if( dist.length() <= 30 )
    {
        _isOpen = true;
        GameManager::Instance()->addItemToScene(_item);
        _item->setPos(this->pos().x() + 50,this->pos().y());
        return true;
    }

    //qWarning() << "chips" << this->_isOpen;
    return false;
}

void Coffre::advance(int /*phase*/)
{
    static GameManager* const gm = GameManager::Instance();

    QLineF dist = QLineF(gm->getPatatePos(),this->pos());

    if(dist.length() <=30 )
        _ouvrable = true;
    else
        _ouvrable = false;

    if(_ouvrable && !_isOpen)
       _popup->show();
    else
       _popup->hide();

}

Item* Coffre::getItem() const
{
    return _item;
}





