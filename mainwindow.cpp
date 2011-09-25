#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(DataBase *db) :
    QMainWindow(0),
    m_ui(new Ui::MainWindow),
    m_airPlaneWidget(new AirPlaneWidget(this, db)),
    m_database(db)
{
    m_ui->setupUi(this);

    setCentralWidget(m_airPlaneWidget);

    connect(m_airPlaneWidget, SIGNAL(notification(QString)),
            this, SLOT(statusBarMsg(QString)));

    connect(m_database, SIGNAL(notification(QString)),
            this, SLOT(statusBarMsg(QString)));
}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_database;
}

void MainWindow::statusBarMsg(const QString msg)
{
    m_ui->statusBar->showMessage(msg, 2000);
}
