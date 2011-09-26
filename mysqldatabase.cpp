#include "mysqldatabase.h"

#include <QSqlQuery>
#include <QSqlRecord>

#include <QVariant>
#include <QDebug>

MysqlDataBase::MysqlDataBase(const QString type,
                             const QString host,
                             const QString pass) :
    m_type(type),
    m_host(host),
    m_pass(pass),
    m_db(0),
    m_connectionIsOpen(false)
{
    m_db = new QSqlDatabase(QSqlDatabase::addDatabase(type));
    m_db->setHostName(m_host);
    m_db->setDatabaseName("airlinedb");
    m_db->setUserName("airline");
    m_db->setPassword(m_pass);
}

MysqlDataBase::~MysqlDataBase()
{
    if (m_connectionIsOpen) {
        m_db->close();
    }
}

bool MysqlDataBase::writeData(const QString id, const bool taken)
{
    QString text;
    bool dummy;
    if (readData(id,dummy)) {
        text = QString("UPDATE seats SET taken=%2 WHERE id='%1'").arg(id).arg(taken);
    } else {
        text = QString("INSERT INTO seats (id, taken) VALUES ('%1', %2)").arg(id).arg(taken);
    }

    QSqlQuery query;
    if (!query.exec(text)) {
        emit notification("SQL - write query falied");
        return false;
    }

    return true;
}

bool MysqlDataBase::readData(const QString id, bool &taken)
{
    if (!m_connectionIsOpen) {
        if (!(m_db->open())) {
            emit notification("Couldn't connect to DB");
            return false;
        }
        m_connectionIsOpen = true;
    }

    QSqlQuery query;
    QString text(QString("SELECT taken FROM seats WHERE id='%1'").arg(id));
    if (!query.exec(text)) {
        emit notification("SQL - read query falied");
        return false;
    }

    QSqlRecord rec = query.record();
    int takenCol = rec.indexOf("taken");
    if (query.next()) {
        taken = query.value(takenCol).toInt();
        return true;
    }

    // not found
    return false;
}
