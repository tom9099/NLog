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



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-nshared-Desktop_Qt_5_7_0_MSVC2015_64bit-Release/release/ -lnshared
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-nshared-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug/debug/ -lnshared
else:unix:!macx: LIBS += -L$$PWD/../build-nshared-Desktop_Qt_5_7_0_MSVC2015_64bit-Release/ -lnshared

INCLUDEPATH += $$PWD/../nshared
DEPENDPATH += $$PWD/../build-nshared-Desktop_Qt_5_7_0_MSVC2015_64bit-Release/release

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-nshared-Desktop_Qt_5_7_0_MSVC2015_64bit-Release/release/libnshared.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-nshared-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug/debug/libnshared.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-nshared-Desktop_Qt_5_7_0_MSVC2015_64bit-Release/release/nshared.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-nshared-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug/debug/nshared.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../build-nshared-Desktop_Qt_5_7_0_MSVC2015_64bit-Release/libnshared.a
