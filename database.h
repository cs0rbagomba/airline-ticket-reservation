#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

class DataBase : public QObject
{
    Q_OBJECT

public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();

    bool writeData(const QString id,
                   const bool taken);

    bool readData(const QString id) const;

signals:

    void dataChanged(QString id);

};

#endif // DATABASE_H
