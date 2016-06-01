#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T09:01:10
#
#-------------------------------------------------

QT       += testlib

TARGET = tst_yksikkotesti
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += C++11

TEMPLATE = app


SOURCES += tst_yksikkotesti.cc \
    ../OmaPuoli/tilasto.cc
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../OmaPuoli/tilasto.hh
    ../KurssinPuoli/tilastorp.hh


# Lisätty jälkeenpäin tiedostojen löytämiseksi
INCLUDEPATH += ../OmaPuoli
INCLUDEPATH += ../KurssinPuoli
DEPENDPATH  += ../OmaPuoli
