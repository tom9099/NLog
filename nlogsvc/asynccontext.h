#ifndef ASYNCCONTEXT_H
#define ASYNCCONTEXT_H

#include <QObject>
#include <QTcpSocket>

class AsyncContext : public QObject
{
    Q_OBJECT

    QString             mIP;
    int                 mPort;
    QTcpSocket          *mSocket;

public:
    explicit AsyncContext(QString ip, int port, QObject *parent = 0);

signals:

    void socketDisconnected();
    void messageReceived(QByteArray bytes);

public slots:

    void init();
    void shutdown();
    void disconnected();
    void readyRead();

};

#endif // ASYNCCONTEXT_H
