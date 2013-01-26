#-------------------------------------------------
#
# Project created by QtCreator 2013-01-26T15:04:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NCClient
TEMPLATE = app


SOURCES += main.cpp\
        ncclientwindow.cpp \
    gui/rcvprogressview.cpp \
    gui/rcvprogressscene.cpp

HEADERS  += ncclientwindow.h \
    gui/rcvprogressview.h \
    gui/rcvprogressscene.h

FORMS    += ncclientwindow.ui
