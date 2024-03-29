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
    inputlistitem.cpp \
    inputaddingdialog.cpp \
    udpinputcreator.cpp \
    lib/midifile/Binasc.cpp \
    lib/midifile/MidiEvent.cpp \
    lib/midifile/MidiEventList.cpp \
    lib/midifile/MidiFile.cpp \
    lib/midifile/MidiMessage.cpp \
    lib/midifile/Options.cpp \
    distortion.cpp \
    generator.cpp \
    effecttreeitem.cpp \
    mixer.cpp \
    effectsequence.cpp \
    effecttreemodel.cpp \
    mixerconfigurator.cpp \
    noopeffect.cpp \
    guitarinputprocessor.cpp \
    guitarcreator.cpp \
    midiinputcreator.cpp \
    midiinput.cpp \
    keyreadinputcreator.cpp

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
    inputlistitem.h \
    inputaddingdialog.h \
    iinputcreator.h \
    udpinputcreator.h \
    lib/midifile/Binasc.h \
    lib/midifile/MidiEvent.h \
    lib/midifile/MidiEventList.h \
    lib/midifile/MidiFile.h \
    lib/midifile/MidiMessage.h \
    lib/midifile/Options.h \
    distortion.h \
    generator.h \
    effecttreeitem.h \
    mixer.h \
    effectsequence.h \
    effecttreemodel.h \
    ieffectconfigurator.h \
    mixerconfigurator.h \
    noparamsconfigurator.h \
    noopeffect.h \
    iinputprocessor.h \
    guitarinputprocessor.h \
    guitarcreator.h \
    midiinputcreator.h \
    midiinput.h \
    keyreadinputcreator.h

FORMS    += mainwindow.ui \
    inputaddingdialog.ui \
    udpinputcreator.ui

CONFIG += c++14
CONFIG += link_pkgconfig
PKGCONFIG += portaudio-2.0
