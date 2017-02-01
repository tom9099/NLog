#ifndef ASYNCCONTEXT_H
#define ASYNCCONTEXT_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class TCP_Client : public QObject
{

    Q_OBJECT

public:

    QTcpSocket  *mSocket;

    TCP_Client(QTcpSocket *socket);
    ~TCP_Client();

signals:
    void removeClient(TCP_Client *client);

public slots:
    void disconnected();
    void readyRead(); // testing only, it acts as a echo server

};


class AsyncContext : public QObject
{
    Q_OBJECT

    QTcpServer                      *mServer;
    QVector<TCP_Client*>            mClients;

public:
    explicit AsyncContext(QObject *parent = 0);

signals:

public slots:

    void init();
    void shutdown();
    void incomingConnection();
    void removeClient(TCP_Client *client);
    void msg(QString msg);
};

#endif // ASYNCCONTEXT_H
