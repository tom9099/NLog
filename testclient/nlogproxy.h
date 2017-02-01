#ifndef NLOGPROXY_H
#define NLOGPROXY_H

#include <QObject>
#include <QThread>
#include "asynccontext.h"


template <typename T>
class Singleton
{
public:
    static T& it()
    {
        static T instance;
        return instance;
    }

};

class NLog : public QObject, public Singleton<NLog>
{
    Q_OBJECT

    QThread             *mWorkerThread;
    AsyncContext        *mContext;

public:
    explicit NLog(QObject *parent = 0);

    void init();
    void msg(QString msg);
    void shutdown();

signals:

    void dispatchMsg(QString msg);

public slots:
};

#endif // NLOGPROXY_H
