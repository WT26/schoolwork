TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += \
    paivays.cpp \
    apufunktiot.cpp \
    kayttoliittyma.cpp \
    paivyri.cpp \
    lista.cpp \
    kirjasto.cpp \
    paivyriohjelma.cpp

HEADERS += \
    paivays.hh \
    apufunktiot.hh \
    kayttoliittyma.hh \
    paivyri.hh \
    lista.hh \
    kirjasto.hh

OTHER_FILES += \
    mun-kalenteri.txt \
    lisattavaa.txt \
    testi.txt \
    tyhja.txt

