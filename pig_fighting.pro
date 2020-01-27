
#-------------------------------------------------
#
# Project created by QtCreator 2019-03-19T18:17:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia


TARGET = pig_fighting
TEMPLATE = app


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG+= static

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    gameobject.cpp \
    ground.cpp \
    person.cpp \
    movingobject.cpp \
    freepig.cpp \
    shotpig.cpp \
    animation.cpp \
    health_field.cpp \
    themostmainwindow.cpp \
    soundplayer.cpp \
    fieldcontroller.cpp \
    resourcestorage.cpp \
    utils.cpp

HEADERS += \
        mainwindow.h \
    gameobject.h \
    ground.h \
    person.h \
    constants.h \
    movingobject.h \
    freepig.h \
    shotpig.h \
    animation.h \
    health_field.h \
    themostmainwindow.h \
    soundplayer.h \
    fieldcontroller.h \
    resourcestorage.h \
    utils.h

FORMS += \
        mainwindow.ui \
    secondwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    textures/sand/middle_block.png \
    textures/sand/right_block.png
