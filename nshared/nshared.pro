#-------------------------------------------------
#
# Project created by QtCreator 2017-02-18T18:36:17
#
#-------------------------------------------------

QT       -= gui

TARGET = nshared
TEMPLATE = lib

DEFINES += NSHARED_LIBRARY

SOURCES += nshared.cpp

HEADERS += nshared.h\
        nshared_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
