#ifndef NSHARED_GLOBAL_H
#define NSHARED_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NSHARED_LIBRARY)
#  define NSHAREDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NSHAREDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NSHARED_GLOBAL_H
