#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

class DataBase : public QObject
{
    Q_OBJECT

public:

    explicit DataBase(QObject *parent = 0);
    virtual ~DataBase();

    // write data to DB, return true on success
    virtual bool writeData(const QString id,
                           const bool taken) = 0;

    // read data from DB, return true on success
    virtual bool readData(const QString id,
                          bool &taken) = 0;

    static DataBase* create();

signals:

    void dataChanged(QString id);
    void notification(const QString msg);

};

#endif // DATABASE_H
