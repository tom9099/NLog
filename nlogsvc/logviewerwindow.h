#ifndef LOGVIEWERWINDOW_H
#define LOGVIEWERWINDOW_H

#include <QDialog>
#include <QThread>
#include <QTimer>
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

public:
    explicit LogViewerWindow(QString ip, int port, QWidget *parent = 0);
    ~LogViewerWindow();

private slots:
    void on_pushButton_clicked();
    void messageReceived(QByteArray bytes);
    void refreshUi();

private:
    Ui::LogViewerWindow *ui;
};

#endif // LOGVIEWERWINDOW_H
