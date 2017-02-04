#ifndef LOGVIEWERWINDOW_H
#define LOGVIEWERWINDOW_H

#include <QDialog>
#include <QThread>

namespace Ui {
class LogViewerWindow;
}

class LogViewerWindow : public QDialog
{
    Q_OBJECT

    QThread             *mNetworkThread;

public:
    explicit LogViewerWindow(QString ip, int port, QWidget *parent = 0);
    ~LogViewerWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LogViewerWindow *ui;
};

#endif // LOGVIEWERWINDOW_H
