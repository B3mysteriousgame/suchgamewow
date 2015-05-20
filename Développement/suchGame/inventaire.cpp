#include "inventaire.hpp"
#include <QMouseEvent>
#include <QDebug>
#include <QCheckBox>

Inventaire::Inventaire(QWidget *parent) : QWidget(parent)
{
    //this->setViewMode(QListView::IconMode);
    //phase de test nocture, a changer avec ItemFactory(ArmeFactory - ArmureFactory - etc) + list de tout les items existants

    _legrid = new QGridLayout;
/*
    Arme *arme1 = new Dragonsword();
    Arme *arme2 = new Longsword();

    QLabel *label = new  QLabel();
    label->setPixmap(arme1->get_pixmap());
    QLabel *label2 = new QLabel();
    label2->setPixmap(arme2->get_pixmap());
    label->setStyleSheet("background-color: grey;");
    label2->setStyleSheet("background-color: grey;");
    _legrid->addWidget(label);
    _legrid->addWidget(label2);*/

    this->setLayout(_legrid);


}

Inventaire::~Inventaire()
{

}
// Sensé affiché une fond différent au passage de la souris ==> ne fonctionne pas !
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

void Inventaire::addItem(Arme *arme)
{

    QLabel *image = new  QLabel();
    QLabel *text = new  QLabel();
    QCheckBox *checkbox = new QCheckBox();

    image->setPixmap(arme->get_pixmap());
    text->setText(arme->get_nom());
    image->setStyleSheet("background-color: grey;");
    text->setStyleSheet("background-color: white;");

    _legrid->addWidget(image,_legrid->rowCount(),0);
    _legrid->addWidget(text,_legrid->rowCount()-1,1);
    _legrid->addWidget(checkbox,_legrid->rowCount()-1,2);

}
/*
void Inventaire::checkEquipement()
{
    int row = 0;
    int column = 1;
    QList<QCheckBox*> listcheckbox = _legrid->findChild;
    foreach(QCheckBox * chk,listcheckbox)
    {
        row++;

        if(chk->isChecked())
        {
           QLabel lelabel=(QLabel) _legrid->itemAtPosition(row,column)->widget()->objectName();
        }
    }
}

*/
