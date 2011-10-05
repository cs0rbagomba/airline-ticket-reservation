#include <QtGui/QApplication>

#include "mainwindow.h"

#include <iostream>

#include "database.h"

void printUsage()
{
    QString error(QString("Usage: %1 [filename][sqltype host password]\n\n"
                          "\t filename:\tXML file to save data. Default value: ~/.seats.xml\n"
                          "\t sqltype:"
                          "\tQDB2\t\tIBM DB2\n"
                          "\t\t\tQIBASE\t\tBorland InterBase Driver\n"
                          "\t\t\tQMYSQL\t\tMySQL Driver\n"
                          "\t\t\tQOCI\t\tOracle Call Interface Driver\n"
                          "\t\t\tQODBC\t\tODBC Driver (includes Microsoft SQL Server)\n"
                          "\t\t\tQPSQL\t\tPostgreSQL Driver\n"
                          "\t\t\tQSQLITE\t\tSQLite version 3 or above\n"
                          "\t\t\tQSQLITE2\tSQLite version 2\n"
                          "\t\t\tQTDS").arg(QApplication::arguments().at(0)));

    std::cerr << error.toStdString() << std::endl;
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // factory method
    DataBase *db = DataBase::create();
    if (!db) {
        printUsage();
        return 1;
    }

    // dependency injection
    MainWindow w(db);
    w.show();

    return a.exec();
}
