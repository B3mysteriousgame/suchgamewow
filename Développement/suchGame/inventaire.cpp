#include "inventaire.hpp"
#include <QMouseEvent>
#include <QDebug>

Inventaire::Inventaire(QWidget *parent) : QWidget(parent)
{
    //this->setViewMode(QListView::IconMode);
    //phase de test nocture, a changer avec ItemFactory(ArmeFactory - ArmureFactory - etc) + list de tout les items existants

    _legrid = new QGridLayout;

    Arme *arme1 = new Dragonsword();
    Arme *arme2 = new Longsword();

    QLabel *label = new  QLabel();
    label->setPixmap(arme1->get_pixmap());
    QLabel *label2 = new QLabel();
    label2->setPixmap(arme2->get_pixmap());
    label->setStyleSheet("background-color: grey;");
    label2->setStyleSheet("background-color: grey;");
    _legrid->addWidget(label);
    _legrid->addWidget(label2);

    this->setLayout(_legrid);


}

Inventaire::~Inventaire()
{

}

void Inventaire::mouseMoveEvent(QMouseEvent *_event)
{
    if(_event->type() == QEvent::Enter)
    {
        int c = this->_legrid->columnCount();
        int r = this->_legrid->rowCount();

        for(int i=0;i < c;i++)
        {
            for(int y=0; y<r ; y++)
            {
                QWidget *chose = this->_legrid->itemAtPosition(i,y)->widget();
                chose->grabMouse();
                QRect zone = chose->geometry();
                chose->setStyleSheet("background-color: white;");
                QWidget *chose2 = new QWidget(chose);
                qWarning() << "chips" << "tarace";
                if(zone.contains(_event->pos()))
                {
                    _legrid->replaceWidget(chose,chose2);
                }
            }
        }
    }
}


