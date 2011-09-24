#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "airplanewidget.h"
#include "database.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DataBase *db);
    ~MainWindow();

public slots:

    void statusBarMsg(const QString msg);

private:
    Ui::MainWindow *m_ui;
    AirPlaneWidget *m_airPlaneWidget;
    DataBase *m_database;
};

#endif // MAINWINDOW_H
