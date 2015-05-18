#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include <QWidget>
#include <QPushButton>
#include <longsword.h>
#include <dragonsword.hpp>
#include <QLabel>
#include <QGridLayout>


class GameManager;


class Inventaire : public QWidget
{
    Q_OBJECT
public:
    explicit Inventaire(QWidget *parent = 0);
    ~Inventaire();
    void mouseMoveEvent(QMouseEvent *_event);

private:

       QPushButton *boutonQuitter, *boutonValider;
       QGridLayout *_legrid;

signals:

public slots:
};

#endif // INVENTAIRE_H
