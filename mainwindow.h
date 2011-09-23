#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "airplanewidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *m_ui;
    AirPlaneWidget *m_airPlaneWidget;
};

#endif // MAINWINDOW_H
