#-------------------------------------------------
#
# Project created by QtCreator 2016-06-04T23:02:58
#
#-------------------------------------------------

QT       += core widgets network

TARGET = qSynth
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pabackend.cpp \
    testcallback.cpp \
    spinlock.cpp \
    keyboardreaderwidget.cpp \
    simplegenerator.cpp \
    guitargenerator.cpp \
    inputlistmodel.cpp \
    udpinput.cpp \
    tc.cpp

HEADERS  += mainwindow.h \
    pabackend.h \
    iaudiobackend.h \
    iaudiocallback.h \
    testcallback.h \
    constants.h \
    spinlock.h \
    iaudioeffect.h \
    igenericinput.h \
    keyboardreaderwidget.h \
    simplegenerator.h \
    genericinputaction.h \
    guitargenerator.h \
    inputlistmodel.h \
    udpinput.h \
    tc.h

FORMS    += mainwindow.ui

CONFIG += c++14
CONFIG += link_pkgconfig
PKGCONFIG += portaudio-2.0
