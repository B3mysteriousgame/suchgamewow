#ifndef ENNEMYFACTORY_H
#define ENNEMYFACTORY_H

#include <Qlist>
#include <QObject>

class Ennemy;
class EnnemyLopette;
class GameManager;
class QTimer;

class EnnemyFactory : public QObject
{
    Q_OBJECT

public:
    EnnemyFactory();
    EnnemyFactory(EnnemyFactory*lol);
    ~EnnemyFactory();

    Ennemy *getEnnemyAt(int listpos);
    int getNbEnnemy();
    void removeEnnemy(Ennemy *it);
    QList<Ennemy*> getListMichel() { return _listeMichels;}
    bool isTimerActive();
    void stop();
    void startTimer(int ms);
    void start();


protected:

    QList<Ennemy*> _listeMichels;
    int            _nombreMichels;

private slots:
    void createEnnemy();

private:
    static const int MAXENN = 10;
    QTimer *_timerPopEnnemy;

};

#endif // ENNEMYFACTORY_H
