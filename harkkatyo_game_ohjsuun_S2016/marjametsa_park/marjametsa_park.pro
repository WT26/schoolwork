TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    view.cpp \
    controller.cpp \
    motor.cpp \
    parkinghall.cpp \
    tampereparking.cpp \
    weapon.cpp \
    character.cpp \
    enemy.cpp \
    playablecharacter.cpp \
    armor.cpp \
    item.cpp \
    implant.cpp \
    gameprogress.cpp \
    battlemap.cpp \
    die.cpp \
    maptile.cpp \
    battleai.cpp \
    xmlparser.cpp



RESOURCES += qml.qrc \
    images.qrc \
    xml.qrc \
    init.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    viewinterface.h \
    view.h \
    motorinterface.h \
    controller.h \
    motor.h \
    tampereparkinginterface.hh \
    parkinghall.hh \
    tampereparking.hh \
    item.h \
    weapon.h \
    enemy.h \
    character.h \
    playablecharacter.h \
    armor.h \
    implant.h \
    gameprogress.h \
    battlemap.h \
    die.h \
    maptile.h \
    battleai.h \
    xmlparser.h \

DISTFILES += \
    saves/example_save.txt \
    saves/save_slot_1.txt \
    saves/save_slot_2.txt \
    saves/save_slot_3.txt
