#-------------------------------------------------
#
# Project created by QtCreator 2015-12-12T12:03:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = palautus-05
TEMPLATE = app


SOURCES += main.cpp\
        paaikkuna.cpp \
    apufunktiot.cpp \
    yksikko.cpp

HEADERS  += paaikkuna.hh \
    apufunktiot.hh \
    yksikko.hh

FORMS    += paaikkuna.ui

OTHER_FILES += \
    saannot.txt
CONFIG += C++11
