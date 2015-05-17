#include "inventaire.hpp"

Inventaire::Inventaire(QWidget *parent) : QWidget(parent)
{
    //this->setViewMode(QListView::IconMode);
    //phase de test nocture, a changer avec ItemFactory(ArmeFactory - ArmureFactory - etc) + list de tout les items existants

    Arme *arme1 = new Dragonsword();
    Arme *arme2 = new Longsword();

    QIcon icone = QIcon(arme1->get_pixmap());
    QIcon icone2 = QIcon(arme2->get_pixmap());

    QLabel *label = new  QLabel();
    label->setPixmap(arme1->get_pixmap());
    QLabel *label2 = new QLabel();
   label2->setPixmap(arme2->get_pixmap());

    QGridLayout *yahourt = new QGridLayout;
    yahourt->addWidget(label);
    yahourt->addWidget(label2);

    this->setLayout(yahourt);


}

Inventaire::~Inventaire()
{

}

