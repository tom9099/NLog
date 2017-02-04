#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logviewerwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{        
    LogViewerWindow viewer(ui->lineEdit_IP->text(), ui->lineEdit_Port->text().toInt());

    this->close();
    viewer.exec();
}
