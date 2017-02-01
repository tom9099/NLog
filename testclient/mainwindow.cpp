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
    mTimer->start(150);
}

void MainWindow::onTimer()
{
    //qDebug() << "16 msec";
    static int i = 0;
    NLog::it().msg(QString("%1. tick\r\n").arg(++i));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    NLog::it().init();
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
}

void MainWindow::on_pushButton_2_clicked()
{    
    NLog::it().shutdown();
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
}
