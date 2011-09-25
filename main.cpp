#include <QtGui/QApplication>

#include "mainwindow.h"

#include <iostream>

#include "database.h"
#include "filedatabase.h"
#include "mysqldatabase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataBase *db;

    if (QApplication::arguments().size() == 1) {
        db = new FileDataBase(QString("%1/.seats.txt").arg(QDir::homePath()));
    } else if (QApplication::arguments().size() == 2) {
        db = new FileDataBase(QApplication::arguments().at(1));
    } else if (QApplication::arguments().size() == 3) {
        db = new MysqlDataBase(QApplication::arguments().at(1),
                               QApplication::arguments().at(2));
    } else {
        QString error(QString("Usage: %1 [filename][ip password]").
               arg(QApplication::arguments().at(0)));

        std::cerr << error.toStdString() << std::endl;
        return 1;
    }


    MainWindow w(db);
    w.show();

    return a.exec();
}
