#include "ennemy.hpp"
#include "gamemanager.hpp"
#include<QDebug>

Ennemy::Ennemy(QGraphicsItem *parent):Personnage(parent)
{
    _sprites.append(":/images/patateSaiyen.png");

    _imgCpt = 0;
    _sens = Ennemy::DROITE;

    setPixmap(QPixmap(":/images/patateSaiyen.png"));
}

Ennemy::~Ennemy()
{

}

int  Ennemy::getImgCpt() const{}
int Ennemy::getSens() const{}
void Ennemy::setSens(const short sens){}

void Ennemy::advance(int step)
    {
        static short cpt = 1, maxTour = 4, maxSprite = 4;
        const qreal maxX = 435, maxY = 354;
        QString spritePAth = ":/images/Sprites/link";
        qreal ddx = 0, ddy = 0, offset = 0.9;

        //_sens = Patate::BAS;
        switch (_sens)
        {
            case Ennemy::DROITE:
                ddx += offset;
                spritePAth.append("D");
                break;
            case Ennemy::GAUCHE:
                ddx += offset * -1.;
                spritePAth.append("G");
                break;
            case Ennemy::BAS:
                ddy += offset;
                spritePAth.append("B");
                break;
            case Ennemy::HAUT:
                ddy += offset * -1.;
                spritePAth.append("H");
                break;
            default:
                break;
        }

        if(cpt >= maxTour) // on repasse a 0
            cpt = 0; // incremente apres donc = 1 la prochaine fois
        else
            if(cpt == 1) // on change l'image
            {
                _imgCpt += 1;

                if(_imgCpt > maxSprite)
                    _imgCpt = 1;

                spritePAth.append(QString::number(_imgCpt));
                setPixmap(QPixmap(spritePAth));
            }

        moveBy(ddx, ddy);

        if(y() > maxY)
            setPos(x(), maxY * -1.);
        else
        {
            if(y() < maxY * -1.)
                setPos(x(), maxY);
            else
            {
                if(x() > maxX)
                    setPos(maxX * -1., y());
                else
                    if(x() < maxX * -1.)
                        setPos(maxX, y());
            }
        }

        qWarning() << "pos: " << x() << " - " << y();
        //GameManager.Instance()->setText(QString("pos: ").append(QString::number(x())).append(" - ").append(QString::number(y())));

        // test collision
        QList<QGraphicsItem*> listCollides = collidingItems();
        if(listCollides.length() > 0)
        {
            foreach (QGraphicsItem *item, listCollides)
            {
                if(item->type() == Ennemy::Type)
                    GameManager::Instance()->removeItem(item);
            }
        }

        ++cpt;
    }
