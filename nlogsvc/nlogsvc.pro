#-------------------------------------------------
#
# Project created by QtCreator 2017-01-26T13:44:59
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nlogsvc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logviewerwindow.cpp \
    asynccontext.cpp \
    settingswindow.cpp

HEADERS  += mainwindow.h \
    logviewerwindow.h \
    asynccontext.h \
    settingswindow.h

FORMS    += mainwindow.ui \
    logviewerwindow.ui \
    settingswindow.ui
