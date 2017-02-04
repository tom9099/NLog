#include "logviewerwindow.h"
#include "ui_logviewerwindow.h"
#include <QHostAddress>

LogViewerWindow::LogViewerWindow(QString ip, int port, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogViewerWindow)
{
    ui->setupUi(this);
    ui->plainTextEdit->setMaximumBlockCount(10000);
    ui->plainTextEdit->setUpdatesEnabled(false);

    mTimer = new QTimer(this);
    mWorkerThread = new QThread(this);
    mContext = new AsyncContext(ip, port);

    mWorkerThread->setObjectName("worker thread");
    mContext->moveToThread(mWorkerThread);
    connect(mWorkerThread, SIGNAL(started()), mContext, SLOT(init()));
    connect(mWorkerThread, SIGNAL(finished()), mContext, SLOT(shutdown()));
    connect(mContext, SIGNAL(socketDisconnected()), this, SLOT(on_pushButton_clicked()));
    connect(mContext, SIGNAL(messageReceived(QByteArray)), this, SLOT(messageReceived(QByteArray)));
    connect(mTimer, SIGNAL(timeout()), this, SLOT(refreshUi()));

    mTimer->start(300);
    mWorkerThread->start();
}

LogViewerWindow::~LogViewerWindow()
{
    mWorkerThread->exit();
    mWorkerThread->wait();
    delete ui;    
}

void LogViewerWindow::on_pushButton_clicked()
{
    this->close();
}

void LogViewerWindow::refreshUi()
{
    ui->plainTextEdit->setUpdatesEnabled(true);
    ui->plainTextEdit->update();
    ui->plainTextEdit->setUpdatesEnabled(false);
}

void LogViewerWindow::messageReceived(QByteArray bytes)
{
    QString msg = bytes;

    ui->plainTextEdit->appendPlainText(msg);
}
