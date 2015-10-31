TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../../palautus-03/kayttoliittyma.cpp \
    ../../palautus-03/main.cpp \
    ../../palautus-03/paivays.cpp \
    ../../palautus-03/paivyri.cpp \
    ../../palautus-03/paivyriohjelma.cpp

SUBDIRS += \
    ../../palautus-03/palautus-03.pro

OTHER_FILES += \
    ../../palautus-03/palautus-03.pro.user

HEADERS += \
    ../../palautus-03/kayttoliittyma.hh \
    ../../palautus-03/paivays.hh \
    ../../palautus-03/paivyri.hh

