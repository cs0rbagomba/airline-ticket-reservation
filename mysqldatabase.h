#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H

#include "database.h"


class MysqlDataBase : public DataBase
{
    Q_OBJECT

public:
    explicit MysqlDataBase(const QString host,
                           const QString pass);
    ~MysqlDataBase();

    // implements DataBase::writeData
    bool writeData(const QString id,
                   const bool taken);

    // implements DataBase::readData
    bool readData(const QString id,
                  bool &taken);

private:

    QString m_host;
    QString m_pass;

};

#endif // MYSQLDATABASE_H
