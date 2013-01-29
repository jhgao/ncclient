#-------------------------------------------------
#
# Project created by QtCreator 2013-01-26T15:04:07
#
#-------------------------------------------------

QT       += core gui network phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NCClient
TEMPLATE = app


SOURCES += main.cpp\
        ncclientwindow.cpp \
    gui/rcvprogressview.cpp \
    gui/rcvprogressscene.cpp \
    protocol/rawblock.cpp \
    protocol/packet.cpp \
    execthread.cpp \
    datahandler.cpp \
    connection.cpp \
    dhudp/rcvblock.cpp \
    dhudp/fragment.cpp \
    dhudp/dhudprcvqueue.cpp \
    dhudp/dhudpdecoder.cpp \
    dhudp/dhudp.cpp \
    dhudp/decparams.cpp \
    dhtcp/dhtcpdecoder.cpp \
    dhtcp/dhtcp.cpp \
    videobuffer.cpp

HEADERS  += ncclientwindow.h \
    gui/rcvprogressview.h \
    gui/rcvprogressscene.h \
    protocol/rawblock.h \
    protocol/protocoltypes.h \
    protocol/ports_define.h \
    protocol/packet.h \
    protocol/cmd_define.h \
    execthread.h \
    datahandler.h \
    connection.h \
    dhudp/rcvblock.h \
    dhudp/fragment.h \
    dhudp/dhudprcvqueue.h \
    dhudp/dhudpprotocol.h \
    dhudp/dhudpdecoder.h \
    dhudp/dhudp.h \
    dhudp/decparams.h \
    dhtcp/dhtcpprotocol.h \
    dhtcp/dhtcpdecoder.h \
    dhtcp/dhtcp.h \
    videobuffer.h

FORMS    += ncclientwindow.ui
