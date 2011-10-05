#include "database.h"

#include <QtGui/QApplication>

#include "filedatabase.h"
#include "sqldatabase.h"

DataBase::DataBase(QObject *parent) :
    QObject(parent)
{

}

DataBase::~DataBase()
{

}

DataBase* DataBase::create()
{
    if (QApplication::arguments().size() == 1) {
        return new FileDataBase(QString("%1/.seats.xml").arg(QDir::homePath()));
    }

    if (QApplication::arguments().size() == 2) {
        return new FileDataBase(QApplication::arguments().at(1));
    }

    if (QApplication::arguments().size() == 4) {
        return new SqlDataBase(QApplication::arguments().at(1),
                               QApplication::arguments().at(2),
                               QApplication::arguments().at(3));
    }

    return 0;
}
