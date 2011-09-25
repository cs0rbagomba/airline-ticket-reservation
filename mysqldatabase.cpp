#include "mysqldatabase.h"

MysqlDataBase::MysqlDataBase(const QString host,
                             const QString pass) :
    m_host(host),
    m_pass(pass)
{

}

MysqlDataBase::~MysqlDataBase()
{

}

bool MysqlDataBase::writeData(const QString id, const bool taken)
{
    Q_UNUSED(id)
    Q_UNUSED(taken)

    return true;
}

bool MysqlDataBase::readData(const QString id, bool &taken)
{
    Q_UNUSED(id)
    Q_UNUSED(taken)

    return true;
}
