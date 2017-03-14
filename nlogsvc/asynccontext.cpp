#include "asynccontext.h"
#include <QThread>
#include <QHostAddress>
#include <QDebug>
#include <QMessageBox>
#include <Windows.h>

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
    if (mSocket->bytesAvailable())
    {
        mNetworkBuffer.append(mSocket->readAll());
    }

    while (mNetworkBuffer.size() >= 4)
    {
        // we've received at least 4 bytes, extract the payload size
        if (mNetworkBuffer.size() >= 4 && mPayloadSize == 0)
        {
            mPayloadSize = int((unsigned char)(mNetworkBuffer[0]) << 24 |
                               (unsigned char)(mNetworkBuffer[1]) << 16 |
                               (unsigned char)(mNetworkBuffer[2]) << 8 |
                               (unsigned char)(mNetworkBuffer[3]));

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
