// http://qt-project.org/doc/qt-4.8/qtestlib-tutorial1.html

#ifndef BALLTESTER_HPP
#define BALLTESTER_HPP

#include <QObject>
#include <QtTest/QtTest>

class BallTester : public QObject
{
    Q_OBJECT

    public:
        explicit BallTester(QObject *parent = 0);

    signals:

    public slots:

    private slots:
         void tester();

};

#endif // BALLTESTER_HPP
