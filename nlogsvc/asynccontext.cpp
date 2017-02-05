#include "asynccontext.h"
#include <QThread>
#include <QHostAddress>
#include <QDebug>

AsyncContext::AsyncContext(QString ip, int port, QObject *parent) : QObject(parent)
{
    mIP = ip;
    mPort = port;
    mPayloadSize = 0;
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

// <4 bytes signed int payload size>|<payload>
void AsyncContext::readyRead()
{
    // read stuff from the network
    mNetworkBuffer.append(mSocket->readAll());

    while (mNetworkBuffer.size() >= 4)
    {
        // we've received at least 4 bytes, extract the payload size
        if (mNetworkBuffer.size() >= 4 && mPayloadSize == 0)
        {
            union
            {
                int x;
                char bytes[4];
            } bytebuffer;

            bytebuffer.bytes[0] = mNetworkBuffer[0];
            bytebuffer.bytes[1] = mNetworkBuffer[1];
            bytebuffer.bytes[2] = mNetworkBuffer[2];
            bytebuffer.bytes[3] = mNetworkBuffer[3];

            mPayloadSize = bytebuffer.x;
            mNetworkBuffer.remove(0, 4);
        }

        // we are waiting for a payload
        if (mPayloadSize > 0)
        {
            // we've got all the bytes
            if (mNetworkBuffer.size() >= mPayloadSize)
            {
                // extract the payload
                mPayload = mNetworkBuffer.left(mPayloadSize);
                mNetworkBuffer.remove(0, mPayloadSize);
                mPayloadSize = 0;
                emit messageReceived(mPayload);
            }
            else
            {
                // the network buffer doesn't contain enough data - bail out
                break ;
            }
        }
    }

    //qDebug() << mNetworkBuffer.size();
}
