#include "algorithmtests.h"

#include <QDebug>

#define protected public

#include "seat.h"

AlgorithmTests::AlgorithmTests(QObject *parent) :
    QObject(parent)
{
}

void AlgorithmTests::testSeat()
{
    // ctor sets 'taken' state to false
    Seat *s1 = new Seat();
    QCOMPARE(s1->taken(), false);

    // set function changes the value
    s1->setTaken();
    QCOMPARE(s1->taken(), true);

    // taken seat cannot be cancelled, only with holding down Ctrl key
    // and saying yes to a dialog
    s1->mousePressEvent(0);
    QCOMPARE(s1->taken(), true);

    // false state can be switched
    s1->setTaken(false);
    s1->mousePressEvent(0);
    QCOMPARE(s1->taken(), true);
}


QTEST_MAIN(AlgorithmTests)
