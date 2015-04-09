#ifndef ENNEMYFACTORY_H
#define ENNEMYFACTORY_H

#include <Qlist>

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


protected:

    QList<Ennemy*> _listeMichels;
    int            _nombreMichels;

private:
    const int MAXENN = 20;

};

#endif // ENNEMYFACTORY_H
