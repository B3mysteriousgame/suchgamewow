#ifndef ENNEMYFACTORY_H
#define ENNEMYFACTORY_H

class Ennemy;
class QList;
class GameManager;

class EnnemyFactory
{
public:
    EnnemyFactory(GameManager gm);
    ~EnnemyFactory();

    Ennemy getEnnemy();
    int getNbEnnemy();

    void createEnnemy();

protected:

    QList<Ennemy*> _listeMichels;
    int            _nombreMichels;
    GameManager    _gm;

};

#endif // ENNEMYFACTORY_H
