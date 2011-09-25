#include <QtGui/QApplication>

#include "mainwindow.h"

#include "database.h"
#include "filedatabase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataBase *db;

    if (QApplication::arguments().size() == 1) {
        db = new FileDataBase(QString("%1/.seats.txt").arg(QDir::homePath()));
    } else {
        db = new FileDataBase(QApplication::arguments().at(1));
    }

    MainWindow w(db);
    w.show();

    return a.exec();
}
