TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    apufunktiot.cpp \
    pala.cpp \
    palapeli.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    apufunktiot.hh \
    pala.hh \
    palapeli.hh

DISTFILES += \
    generoitu01.txt

