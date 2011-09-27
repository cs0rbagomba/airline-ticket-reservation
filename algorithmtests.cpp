#include "algorithmtests.h"

#include <QTest>
#include <QDebug>
#include <QSignalSpy>


//#define private public

#include "filedatabase.h"



AlgorithmTests::AlgorithmTests(QObject *parent) :
    QObject(parent)
{
}

void AlgorithmTests::basicTest()
{

}

void AlgorithmTests::FileDataBaseTest()
{
    bool taken;

    /// Read from file without permissions
    {
        QFile file(QString("%1/noperm.xml").arg(QDir::tempPath()));
        file.remove();
        file.open(QIODevice::WriteOnly);
        file.setPermissions(0);

        FileDataBase db(QString("%1/noperm.xml").arg(QDir::tempPath()));
        QSignalSpy spy(&db, SIGNAL(notification(const QString)));

        QCOMPARE(db.readData("1a",taken), false);
        QCOMPARE(spy.count(), 1);
        QList<QVariant> arguments = spy.takeFirst();
        QCOMPARE(arguments.at(0).toString(), QString("Couldn't read file"));

        file.remove();
    }

    /// Read from non-existing file, check creation
    {
        QFile file(QString("%1/nonexist.xml").arg(QDir::tempPath()));
        file.remove();

        FileDataBase db(QString("%1/nonexist.xml").arg(QDir::tempPath()));
        QSignalSpy spy(&db, SIGNAL(notification(const QString)));

        QCOMPARE(db.readData("1a",taken), false);
        QCOMPARE(spy.count(), 0);

        file.open(QIODevice::ReadOnly);
        QTextStream ts(&file);
        QCOMPARE(ts.readAll(), QString("<!DOCTYPE AirLine_Seat_Allocation>\n"
                                       "<Seats/>\n"));
        file.remove();
    }

    /// Read from existing, but not in valid XML file
    {
        QFile file(QString("%1/invalid.xml").arg(QDir::tempPath()));
        file.remove();
        file.open(QIODevice::WriteOnly);
        QTextStream ts(&file);
        ts << QString("seat id=8c taken=1");
        file.close();

        FileDataBase db(QString("%1/invalid.xml").arg(QDir::tempPath()));
        QSignalSpy spy(&db, SIGNAL(notification(const QString)));

        QCOMPARE(db.readData("1a",taken), false);
        QCOMPARE(spy.count(), 1);
        QList<QVariant> arguments = spy.takeFirst();
        QCOMPARE(arguments.at(0).toString(),
                 QString("Couldn't parse XML file"));

        file.remove();
    }

    /// Read from file, non-existing data
    {
        QFile file(QString("%1/nodata.xml").arg(QDir::tempPath()));
        file.remove();
        file.open(QIODevice::WriteOnly);
        QTextStream ts(&file);
        ts << QString("<!DOCTYPE AirLine_Seat_Allocation>\n"
                      "<Seats/>\n");
        file.close();

        FileDataBase db(QString("%1/nodata.xml").arg(QDir::tempPath()));
        QSignalSpy spy(&db, SIGNAL(notification(const QString)));

        QCOMPARE(db.readData("1a",taken), false);
        QCOMPARE(spy.count(), 0);
        file.remove();
    }

    /// Read from file, existing data
    {
        QFile file(QString("%1/dataexists.xml").arg(QDir::tempPath()));
        file.remove();
        file.open(QIODevice::WriteOnly);
        QTextStream ts(&file);
        ts << QString("<!DOCTYPE AirLine_Seat_Allocation>\n"
                      "<Seats>\n"
                      " <seat id=\"3b\" taken=\"1\"/>\n"
                      " <seat id=\"4c\" taken=\"0\"/>\n"
                      "</Seats>\n");
        file.close();

        FileDataBase db(QString("%1/dataexists.xml").arg(QDir::tempPath()));
        QSignalSpy spy(&db, SIGNAL(notification(const QString)));


        QCOMPARE(db.readData("3b",taken), true);
        QCOMPARE(taken, true);
        QCOMPARE(spy.count(), 0);

        QCOMPARE(db.readData("4c",taken), true);
        QCOMPARE(taken, false);
        QCOMPARE(spy.count(), 0);

        file.remove();
    }

    /// Write to file
    {
        QFile file(QString("%1/datacreated.xml").arg(QDir::tempPath()));
        file.remove();
        file.open(QIODevice::WriteOnly);
        QTextStream ts(&file);
        ts << QString("<!DOCTYPE AirLine_Seat_Allocation>\n"
                      "<Seats/>\n");
        file.close();

        FileDataBase db(QString("%1/datacreated.xml").arg(QDir::tempPath()));
        QSignalSpy spy(&db, SIGNAL(notification(const QString)));


        QCOMPARE(db.writeData("12a",true), true);
        QCOMPARE(spy.count(), 0);

        QCOMPARE(db.writeData("3d",false), true);
        QCOMPARE(spy.count(), 0);

        file.open(QIODevice::ReadOnly);
        QCOMPARE(ts.readAll(), QString("<!DOCTYPE AirLine_Seat_Allocation>\n"
                                       "<Seats>\n"
                                       " <seat id=\"12a\" taken=\"1\"/>\n"
                                       " <seat id=\"3d\" taken=\"0\"/>\n"
                                       "</Seats>\n"));

        file.remove();
    }

    /// Write to readonly file
    {
        QFile file(QString("%1/readonly.xml").arg(QDir::tempPath()));
        file.remove();
        file.open(QIODevice::WriteOnly);
        QTextStream ts(&file);
        ts << QString("<!DOCTYPE AirLine_Seat_Allocation>\n"
                      "<Seats/>\n");
        file.close();
        file.setPermissions(QFile::ReadOwner);

        FileDataBase db(QString("%1/readonly.xml").arg(QDir::tempPath()));
        QSignalSpy spy(&db, SIGNAL(notification(const QString)));

        QCOMPARE(db.writeData("12a",true), false);
        QCOMPARE(spy.count(), 1);
        QList<QVariant> arguments = spy.takeFirst();
        QCOMPARE(arguments.at(0).toString(),
                 QString("Couldn't open file to write"));

        file.remove();
    }
}

QTEST_MAIN(AlgorithmTests)
