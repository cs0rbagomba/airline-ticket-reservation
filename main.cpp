#include <QtGui/QApplication>

#include "mainwindow.h"

#include <iostream>

#include "database.h"
#include "filedatabase.h"
#include "sqldatabase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // DB interface
    DataBase *db;

    if (QApplication::arguments().size() == 1) {
        db = new FileDataBase(QString("%1/.seats.xml").arg(QDir::homePath()));
    } else if (QApplication::arguments().size() == 2) {
        db = new FileDataBase(QApplication::arguments().at(1));
    } else if (QApplication::arguments().size() == 4) {
        db = new SqlDataBase(QApplication::arguments().at(1),
                             QApplication::arguments().at(2),
                             QApplication::arguments().at(3));
    } else {
        QString error(QString("Usage: %1 [filename][sqltype host password]\n\n"
                              "\t filename:     XML file to save data. Default value: ~/.seats.xml"
                              "\t sqltype:\n"
                              "\t\tQDB2	IBM DB2\n"
                              "\t\tQIBASE	Borland InterBase Driver\n"
                              "\t\tQMYSQL	MySQL Driver\n"
                              "\t\tQOCI	Oracle Call Interface Driver\n"
                              "\t\tQODBC	ODBC Driver (includes Microsoft SQL Server)\n"
                              "\t\tQPSQL	PostgreSQL Driver\n"
                              "\t\tQSQLITE	SQLite version 3 or above\n"
                              "\t\tQSQLITE2	SQLite version 2\n"
                              "\t\tQTDS").
               arg(QApplication::arguments().at(0)));

        std::cerr << error.toStdString() << std::endl;
        return 1;
    }

    // dep.injection pattern
    MainWindow w(db);
    w.show();

    return a.exec();
}
