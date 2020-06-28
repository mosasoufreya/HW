QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attack_enemy.cpp \
    basic_bullet.cpp \
    basic_enemy.cpp \
    basic_tower.cpp \
    boss.cpp \
    bullet.cpp \
    enemy.cpp \
    enemy_bullet.cpp \
    ice_bullet.cpp \
    ice_tower.cpp \
    introduction.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    mybutton.cpp \
    scene.cpp \
    sun_bullet.cpp \
    sun_tower.cpp \
    tower.cpp \
    towerposition.cpp \
    waypoint.cpp

HEADERS += \
    attack_enemy.h \
    basic_bullet.h \
    basic_enemy.h \
    basic_tower.h \
    boss.h \
    bullet.h \
    enemy.h \
    enemy_bullet.h \
    ice_bullet.h \
    ice_tower.h \
    introduction.h \
    mainwindow.h \
    menu.h \
    mybutton.h \
    scene.h \
    sun_bullet.h \
    sun_tower.h \
    tower.h \
    towerposition.h \
    waypoint.h

FORMS += \
    mainwindow.ui \
    scene.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
