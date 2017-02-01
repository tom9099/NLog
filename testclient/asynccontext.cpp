#include "asynccontext.h"
#include <QDataStream>
#include <QFile>

TCP_Client::TCP_Client(QTcpSocket *socket) : QObject()
{
    mSocket = socket;
    qDebug() << "TCP_Client::TCP_Client";
}

TCP_Client::~TCP_Client()
{
    emit removeClient(this);
    delete mSocket;
    qDebug() << "TCP_Client::~TCP_Client()";
}

void TCP_Client::disconnected()
{
    deleteLater();
}

void TCP_Client::readyRead()
{
    QByteArray data = mSocket->readAll();

    // echo
    mSocket->write(data);
}


AsyncContext::AsyncContext(QObject *parent) : QObject(parent)
{

}

void AsyncContext::init()
{
    mServer = new QTcpServer();
    connect(mServer, SIGNAL(newConnection()), this, SLOT(incomingConnection()));

    mServer->listen(QHostAddress("127.0.0.1"), 9099);
}

void AsyncContext::shutdown()
{
    while (!mClients.empty())
    {
        TCP_Client *client = *mClients.begin();
        delete client;
    }

    mServer->close();
    delete mServer;
}


void AsyncContext::removeClient(TCP_Client *client)
{
   mClients.removeAll(client);
}

void AsyncContext::msg(QString msg)
{    
    for (TCP_Client *client : mClients)
    {
        client->mSocket->write(msg.toStdString().c_str(), msg.size());
    }
}

void AsyncContext::incomingConnection()
{
    qDebug() << "incomingConnection";

    while (mServer->hasPendingConnections())
    {
        TCP_Client *client = new TCP_Client(mServer->nextPendingConnection());

        connect(client->mSocket, SIGNAL(disconnected()), client, SLOT(disconnected()));
        connect(client, SIGNAL(removeClient(TCP_Client*)), this, SLOT(removeClient(TCP_Client*)));
        connect(client->mSocket, SIGNAL(readyRead()), client, SLOT(readyRead()));

        mClients.push_back(client);
    }
}
