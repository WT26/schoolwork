TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    paivyriohjelma.cpp \
    paivays.cpp \
    paivyri.cpp \
    apufunktiot.cpp \
    lista.cpp \
    kirjasto.cpp \
    kayttoliittyma.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    paivays.hh \
    paivyri.hh \
    apufunktiot.hh \
    lista.hh \
    kirjasto.hh \
    kayttoliittyma.hh

DISTFILES += \
    mun-kalenteri.txt

