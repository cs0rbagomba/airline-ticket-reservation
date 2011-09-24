#include <QtGui/QApplication>

#include "mainwindow.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataBase db;


    MainWindow w(&db);
    w.show();

    return a.exec();
}
