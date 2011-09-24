#include "database.h"

DataBase::DataBase(QObject *parent) :
    QObject(parent)
{

}

DataBase::~DataBase()
{

}

bool DataBase::writeData(const QString id, const bool taken)
{
    QString msg = QString("Writing to DB: %1 -> %2").arg(id).arg(taken);
    qDebug(msg.toStdString().c_str());

    return true;
}

bool DataBase::readData(const QString id) const
{
    QString msg = QString("Reading from DB: %1").arg(id);
    qDebug(msg.toStdString().c_str());

    return false;
}
