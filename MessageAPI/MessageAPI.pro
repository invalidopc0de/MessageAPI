#-------------------------------------------------
#
# Project created by QtCreator 2011-04-17T16:45:01
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = MessageAPI
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    udpobjects.cpp \
    broadcastservice.cpp

HEADERS += messageapi.h \
    udpobjects.h \
    broadcastservice.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/local/lib
    }
    INSTALLS += target
}
