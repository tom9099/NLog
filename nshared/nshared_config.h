#ifndef NSHARED_CONFIG_H_
#define NSHARED_CONFIG_H_

#include <QMutex>
#include <QString>
#include <QMap>

#include "nshared_global.h"

class NSHAREDSHARED_EXPORT NConfig
{

protected:

    QMap<QString, QString>          mProperties;
    QMutex                          mCfgMutex;

    void loadDefault();    

public:

    NConfig();

    void init();
    void save();

    static NConfig& it();

    int getInt32(const QString &name, int defaultValue);

};

#endif /*NSHARED_CONFIG_H_*/
