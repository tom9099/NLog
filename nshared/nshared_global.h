#ifndef NSHARED_GLOBAL_H
#define NSHARED_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NSHARED_LIBRARY)
#  define NSHAREDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NSHAREDSHARED_EXPORT Q_DECL_IMPORT
#endif

#if _WIN64
    #define NS_WINDOWS 1
    #define NS_LINUX 0
#else
    #define NS_WINDOWS 0
    #define NS_LINUX 1
#endif

#endif // NSHARED_GLOBAL_H
