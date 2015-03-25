#ifndef ENNEMYFACTORY_H
#define ENNEMYFACTORY_H

#include <Qlist>
#include <QTimer>

class Ennemy;
class GameManager;

class EnnemyFactory
{
public:
    EnnemyFactory();
    ~EnnemyFactory();

    Ennemy getEnnemyAt(int listpos);
    int getNbEnnemy();
    void createEnnemy();
    void startTimerPopEnnemy();


protected:

    QList<Ennemy*> _listeMichels;
    int            _nombreMichels;
    GameManager    *_gm;
    QTimer         *_timerPopEnnemy;

};

#endif // ENNEMYFACTORY_H
