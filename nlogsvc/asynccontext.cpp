#include "asynccontext.h"
#include <QThread>
#include <QHostAddress>
#include <QDebug>

AsyncContext::AsyncContext(QString ip, int port, QObject *parent) : QObject(parent)
{
    mIP = ip;
    mPort = port;
}

void AsyncContext::init()
{    
    mSocket = new QTcpSocket(this);

    connect(mSocket, SIGNAL(disconnected()),     this, SLOT(disconnected()));
    connect(mSocket, SIGNAL(readyRead()),        this, SLOT(readyRead()));

    mSocket->connectToHost(QHostAddress(mIP), mPort);
}

void AsyncContext::shutdown()
{
    mSocket->close();
}

void AsyncContext::disconnected()
{
    // emit a signal to notify the main window
    emit socketDisconnected();
}

void AsyncContext::readyRead()
{
    QByteArray bytes = mSocket->readAll();

    emit messageReceived(bytes);
}
