#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T08:59:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OmaPuoli
TEMPLATE = lib
CONFIG += c++11
CONFIG += staticlib
CONFIG += console

# Lisätty kurssin puolen tavaroiden käyttämiseksi
INCLUDEPATH += $$PWD/../KurssinPuoli
DEPENDPATH += $$PWD/../KurssinPuoli
#LIBS += $$PWD/../KurssinPuoli/sijainti.o


SOURCES += \
    luopeli.cc \
    tilasto.cc \
    pelinakyma.cc \
    kaupunki.cc \
    funktiot.cc \
    drooni.cc \
    alkukuva.cc

HEADERS  += \
    kaupunki.hh \
    tilasto.hh \
    pelinakyma.hh \
    alkukuva.hh \
    drooni.hh \
    funktiot.hh
FORMS += \
    pelinakyma.ui \
    alkukuva.ui

OTHER_FILES +=

RESOURCES += \
    kuvat.qrc
