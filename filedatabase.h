#ifndef FILEDATABASE_H
#define FILEDATABASE_H

#include "database.h"

#include <QtXml>
#include <QFileSystemWatcher>

class FileDataBase : public DataBase
{
    Q_OBJECT

public:

    explicit FileDataBase(const QString filePath);
    ~FileDataBase();

    // implements DataBase::writeData
    bool writeData(const QString id,
                   const bool taken);

    // implements DataBase::readData
    bool readData(const QString id,
                  bool &taken);

private slots:

    void fileModified(const QString&);

private:

    bool loadData(const bool calculateDiff = false);
    bool initFile();


    QString m_filePath;
    bool m_fileIsLoaded;
    QDomDocument m_domDoc;
    QMap<QString, bool> m_seats;
    QFileSystemWatcher m_watcher;
};

#endif // FILEDATABASE_H
