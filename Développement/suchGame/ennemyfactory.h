#ifndef ENNEMYFACTORY_H
#define ENNEMYFACTORY_H

#include <Qlist>

class Ennemy;
class EnnemyLopette;
class GameManager;

class EnnemyFactory
{
public:
    EnnemyFactory();
    ~EnnemyFactory();

    Ennemy *getEnnemyAt(int listpos);
    int getNbEnnemy();
    void createEnnemy();
    void removeEnnemy(Ennemy *it);


protected:

    QList<Ennemy*> _listeMichels;
    int            _nombreMichels;

private:
    static const int MAXENN = 20;

};

#endif // ENNEMYFACTORY_H
