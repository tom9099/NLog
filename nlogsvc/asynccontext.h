#ifndef ASYNCCONTEXT_H
#define ASYNCCONTEXT_H

#include <QObject>

class AsyncContext : public QObject
{
    Q_OBJECT
public:
    explicit AsyncContext(QObject *parent = 0);

signals:

public slots:
};

#endif // ASYNCCONTEXT_H