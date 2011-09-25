#include <QtGui/QApplication>

#include "mainwindow.h"

#include "database.h"
#include "filedatabase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataBase *db = new FileDataBase(".cica.txt");


    MainWindow w(db);
    w.show();

    return a.exec();
}
