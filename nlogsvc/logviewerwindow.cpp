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

    mUILastUpdated = mUIUpdateTimer.elapsed();
    mSkippedmessages = 0;
    mTotalBytesReceived = 0;
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
    mUILastUpdated = mUIUpdateTimer.elapsed();
}

void LogViewerWindow::messageReceived(QByteArray bytes)
{
    mTotalBytesReceived += bytes.length();

    if (mUIUpdateTimer.elapsed() - mUILastUpdated < 750)
    {
        QString msg = bytes;
        ui->plainTextEdit->appendPlainText(msg);
        if (mSkippedmessages)
        {
            QString s = QString("*** %1 Messages Were Skipped***").arg(mSkippedmessages);
            ui->plainTextEdit->appendPlainText(s);
            this->setWindowTitle(s);
        }
        mSkippedmessages = 0;
    }
    else
    {
        mSkippedmessages++;
    }
}
