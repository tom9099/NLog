#ifndef NSHARED_GLOBAL_H
#define NSHARED_GLOBAL_H

#include <QtCore/qglobal.h>

#define NS_NONCOPYABLE(classname) \
    classname(); \
    classname( const classname& other ); \
    classname& operator=( const classname& );

#if defined(NSHARED_LIBRARY)
#  define NSHAREDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NSHAREDSHARED_EXPORT Q_DECL_IMPORT
#endif

#if _WIN64
    #define NS_WINDOWS 1
    #define NS_LINUX 0
#elif __linux__
    #define NS_WINDOWS 0
    #define NS_LINUX 1
#else
#error "What are you?? _WIN64 or __linux__ must be defined."
#endif

#endif // NSHARED_GLOBAL_H
