#include "nlogproxy.h"

NLog::NLog(QObject *parent) : QObject(parent)
{

}

void NLog::init()
{
    mWorkerThread = new QThread();
    mContext = new AsyncContext();

    mWorkerThread->setObjectName("NLog Thread");
    mContext->moveToThread(mWorkerThread);
    connect(mWorkerThread, SIGNAL(started()), mContext, SLOT(init()));
    connect(mWorkerThread, SIGNAL(finished()), mContext, SLOT(shutdown()));

    mWorkerThread->start();
}

void NLog::msg(QString msg)
{

}

void NLog::shutdown()
{
    mWorkerThread->exit();
    mWorkerThread->wait();
    delete mContext;
    delete mWorkerThread;
}
