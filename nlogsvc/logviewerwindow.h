#ifndef LOGVIEWERWINDOW_H
#define LOGVIEWERWINDOW_H

#include <QDialog>
#include <QThread>
#include <QTimer>
#include <QElapsedTimer>
#include "asynccontext.h"

namespace Ui {
class LogViewerWindow;
}

class LogViewerWindow : public QDialog
{
    Q_OBJECT

    QThread             *mWorkerThread;
    AsyncContext        *mContext;
    QTimer              *mTimer;
    QElapsedTimer       mUIUpdateTimer;
    qint64              mUILastUpdated;
    int                 mSkippedmessages;
    qint64              mTotalBytesReceived;
    qint64              mTotalMessages;
    qint64              mMessagesPerSec;
    qint64              mMsgPerSecTimer;

public:
    explicit LogViewerWindow(QString ip, int port, QWidget *parent = 0);
    ~LogViewerWindow();

private slots:
    void on_pushButton_clicked();
    void messageReceived(QByteArray bytes);
    void refreshUi();

    void on_pushButton_2_clicked();

private:
    Ui::LogViewerWindow *ui;
};

#endif // LOGVIEWERWINDOW_H
