TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += \
    kayttoliittyma.cpp \
    paivays.cpp \
    paivyri.cpp \
    paivyriohjelma.cpp \
    apufunktiot.cpp

OTHER_FILES += \
    palautus-03.pro.user \
    mun-kalenteri.txt \
    tyhja.txt

HEADERS += \
    kayttoliittyma.hh \
    paivays.hh \
    paivyri.hh \
    apufunktiot.hh

