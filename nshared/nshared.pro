#-------------------------------------------------
#
# Project created by QtCreator 2017-02-18T18:36:17
#
#-------------------------------------------------

QT       -= gui

TARGET = nshared
TEMPLATE = lib

DEFINES += NSHARED_LIBRARY

SOURCES += nshared.cpp \
    nshared_config.cpp

HEADERS += nshared.h\
        nshared_global.h \
    xml/rapidxml.hpp \
    xml/rapidxml_iterators.hpp \
    xml/rapidxml_print.hpp \
    xml/rapidxml_utils.hpp \
    nshared_config.h

win32:LIBS += -luser32

unix {
    target.path = /usr/lib
    INSTALLS += target
}
