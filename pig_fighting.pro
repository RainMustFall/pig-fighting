
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
    ground.cpp \
    person.cpp \
    animation.cpp \
    health_field.cpp \
    utils.cpp \
    main_window.cpp \
    sound_player.cpp \
    shot_pig.cpp \
    resource_storage.cpp \
    field_view.cpp \
    free_pig.cpp \
    game_object.cpp \
    moving_object.cpp \
    field_controller.cpp

HEADERS += \
    ground.h \
    person.h \
    constants.h \
    animation.h \
    health_field.h \
    utils.h \
    field_controller.h \
    field_view.h \
    main_window.h \
    sound_player.h \
    shot_pig.h \
    free_pig.h \
    game_object.h \
    moving_object.h \
    resource_storage.h

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
