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

    mMsgPerSecTimer = mUILastUpdated = mUIUpdateTimer.elapsed();
    mSkippedmessages = 0;
    mTotalBytesReceived = 0;
    mTotalMessages = 0;
    mMessagesPerSec = 0;
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
    qint64 elapsed = mUIUpdateTimer.elapsed();
    mTotalBytesReceived += bytes.size();
    //qDebug() << elapsed - mMsgPerSecTimer;
    if ((elapsed - mMsgPerSecTimer) > 1000)
    {
        mMsgPerSecTimer = elapsed;

        this->setWindowTitle(QString("Mesages: %1 Msg/sec: %2 Total bytes: %3 KB").arg(mTotalMessages).arg(mTotalMessages - mMessagesPerSec).arg(mTotalBytesReceived / 1024));
        mMessagesPerSec = mTotalMessages;
    }

    if (elapsed - mUILastUpdated < 2500)
    {
        QString msg = bytes;
        ui->plainTextEdit->appendPlainText(msg);
        mTotalMessages++;
        if (mSkippedmessages)
        {
            QString s = QString("*** %1 Messages Were Skipped***").arg(mSkippedmessages);
            ui->plainTextEdit->appendPlainText(s);
            //qDebug() << s;
            mSkippedmessages = 0;
        }        
    }
    else
    {
        mSkippedmessages++;
    }
}
