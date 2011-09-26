#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H


/**
 * @note init SQL Database:
 *
 * CREATE DATABASE airlinedb;
 * SHOW DATABASES;
 * USE airlinedb;
 * GRANT ALL ON airlinedb.* TO 'airline'@'localhost' IDENTIFIED BY 'airlinepass';
 * CREATE TABLE seats ( id varchar(255) NOT NULL UNIQUE PRIMARY KEY, taken int NOT NULL);
 */

#include "database.h"

#include <QtSql/QSqlDatabase>


/// @todo Re-write it SQL generic, it's just a string in the ctor...
class MysqlDataBase : public DataBase
{
    Q_OBJECT

public:
    explicit MysqlDataBase(const QString type,
                           const QString host,
                           const QString pass);
    ~MysqlDataBase();

    // implements DataBase::writeData
    bool writeData(const QString id,
                   const bool taken);

    // implements DataBase::readData
    bool readData(const QString id,
                  bool &taken);

private:

    QString m_type; // QDB2, QIBASE, QMYSQL, QOCI , QODBC, QPSQL, QSQLITE, QSQLITE2, QTDS
    QString m_host;
    QString m_pass;
    QSqlDatabase *m_db;
    bool m_connectionIsOpen;

};

#endif // MYSQLDATABASE_H
