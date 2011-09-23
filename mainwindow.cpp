#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_airPlaneWidget(new AirPlaneWidget(this))
{
    m_ui->setupUi(this);

    setCentralWidget(m_airPlaneWidget);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
