#-------------------------------------------------
#
# Project created by QtCreator 2017-01-26T13:43:16
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testclient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nlogproxy.cpp \
    asynccontext.cpp

HEADERS  += mainwindow.h \
    nlogproxy.h \
    asynccontext.h

FORMS    += mainwindow.ui



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-nshared-Desktop_Qt_5_9_1_MSVC2015_64bit-Release/release/ -lnshared
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-nshared-Desktop_Qt_5_9_1_MSVC2015_64bit-Debug/debug/ -lnshared

else:unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-nshared-Desktop_Qt_5_9_1_GCC_64bit-Release/ -lnshared
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-nshared-Desktop_Qt_5_9_1_GCC_64bit-Debug/ -lnshared

INCLUDEPATH += $$PWD/../nshared
DEPENDPATH += $$PWD/../build-nshared-Desktop_Qt_5_9_1_MSVC2015_64bit-Release/release
DEPENDPATH += $$PWD/../build-nshared-Desktop_Qt_5_9_1_MSVC2015_64bit-Debug/debug

#
# 32bit windows?
#
win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-nshared-Desktop_Qt_5_9_1_MSVC2015_64bit-Release/release/libnshared.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-nshared-Desktop_Qt_5_9_1_MSVC2015_64bit-Debug/debug/libnshared.a

#
# 64bit windows??
#
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-nshared-Desktop_Qt_5_9_1_MSVC2015_64bit-Release/release/nshared.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-nshared-Desktop_Qt_5_9_1_MSVC2015_64bit-Debug/debug/nshared.lib

#
# linux?? (32 or 64bit?)
#
else:unix:!macx:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-nshared-Desktop_Qt_5_9_1_GCC_64bit-Release/libnshared.so
else:unix:!macx:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-nshared-Desktop_Qt_5_9_1_GCC_64bit-Debug/libnshared.so
