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
