#ifndef ENNEMYFACTORY_H
#define ENNEMYFACTORY_H

#include <Qlist>
#include <QObject>

class Ennemy;
class GameManager;
class QTimer;

class EnnemyFactory : public QObject
{
    Q_OBJECT

public:
    EnnemyFactory();
    ~EnnemyFactory();

    Ennemy *getEnnemyAt(int listpos);
    int getNbEnnemy();
    void removeEnnemy(Ennemy *it);
    bool isTimerActive();
    void stopTimer();
    void startTimer(int ms);
    void start();


protected:

    QList<Ennemy*> _listeMichels;
    int            _nombreMichels;

private slots:
    void createEnnemy();

private:
    static const int MAXENN = 20;
    QTimer *_timerPopEnnemy;

};

#endif // ENNEMYFACTORY_H
