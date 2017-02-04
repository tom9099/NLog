#include "logviewerwindow.h"
#include "ui_logviewerwindow.h"
#include <QHostAddress>

LogViewerWindow::LogViewerWindow(QString ip, int port, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogViewerWindow)
{
    ui->setupUi(this);

    mNetworkThread = new QThread(this);
}

LogViewerWindow::~LogViewerWindow()
{
    mNetworkThread->exit();
    mNetworkThread->wait();
    delete ui;    
}

void LogViewerWindow::on_pushButton_clicked()
{
    this->close();
}
