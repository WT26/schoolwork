TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

SOURCES += \
    kayttoliittyma.cpp \
    paivays.cpp \
    paivyri.cpp \
    paivyriohjelma.cpp

OTHER_FILES += \
    palautus-03.pro.user

HEADERS += \
    kayttoliittyma.hh \
    paivays.hh \
    paivyri.hh

