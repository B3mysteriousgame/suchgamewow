#include "simpleanim.hpp"
#include <QTimer>

SimpleAnim::SimpleAnim(QObject *parent) :
    QPropertyAnimation(parent)
{
    _tima = new QTimer();
}

void SimpleAnim::doYaShit()
{
    iDoMyShit();
}

void SimpleAnim::iDoMyShit()
{
    // TODO: do dat shit
}
