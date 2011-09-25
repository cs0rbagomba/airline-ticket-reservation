#ifndef FILEDATABASE_H
#define FILEDATABASE_H

#include "database.h"

#include <QtXml>
#include <QFileSystemWatcher>

class FileDataBase : public DataBase
{
public:

    explicit FileDataBase(const QString filePath);
    ~FileDataBase();

    // write data to DB, return true on success
    bool writeData(const QString id,
                   const bool taken);

    // read data from DB, return true on success
    bool readData(const QString id,
                  bool &taken);

private slots:

    void fileModified(const QString&);

private:

    bool loadData();
    bool initFile();


    QString m_filePath;
    bool m_fileIsLoaded;
    QDomDocument m_domDoc;
    QMap<QString, bool> m_seats;
    QFileSystemWatcher m_watcher;
};

#endif // FILEDATABASE_H
