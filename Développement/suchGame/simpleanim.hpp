#ifndef SIMPLEANIM_HPP
#define SIMPLEANIM_HPP

#include <QObject>
#include <QPropertyAnimation>

class QTimer;

class SimpleAnim : public QPropertyAnimation
{
public:
    explicit SimpleAnim(QObject *parent = 0);
    void start();

signals:

public slots:
    void doYaShit();

protected:
    QTimer *_tima;
    void iDoMyShit();

};

#endif // SIMPLEANIM_HPP
