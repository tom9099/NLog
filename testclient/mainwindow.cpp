#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mTimer = new QTimer(this);

    connect(mTimer, SIGNAL(timeout()), this, SLOT(onTimer()));
    mTimer->start(16);
}

void MainWindow::onTimer()
{
    //qDebug() << "16 msec";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    NLog::it().init();
}

void MainWindow::on_pushButton_2_clicked()
{
    NLog::it().shutdown();
}
