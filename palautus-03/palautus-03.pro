TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    apufunktiot.cpp \
    paivays.cpp \
    paivyri.cpp \
    kayttoliittyma.cpp \
    paivyriohjelma.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    apufunktiot.hh \
    paivays.hh \
    paivyri.hh \
    kayttoliittyma.hh

DISTFILES += \
    mun-kalenteri.txt

