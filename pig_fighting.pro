
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
    source_code/game_objects/game_object.cpp \
    source_code/game_objects/ground.cpp \
    source_code/game_objects/health_field.cpp \
    source_code/game_objects/moving_object.cpp \
    source_code/game_objects/person.cpp \
    source_code/game_objects/pig_classes/free_pig.cpp \
    source_code/game_objects/pig_classes/shot_pig.cpp \
    source_code/main.cpp \
    source_code/utils/animation.cpp \
    source_code/utils/resource_storage.cpp \
    source_code/utils/sound_player.cpp \
    source_code/utils/utils.cpp \
    source_code/view_controller/field_controller.cpp \
    source_code/view_controller/field_view.cpp \
    source_code/view_controller/main_window.cpp \

HEADERS += \
    source_code/game_objects/game_object.h \
    source_code/game_objects/ground.h \
    source_code/game_objects/health_field.h \
    source_code/game_objects/moving_object.h \
    source_code/game_objects/person.h \
    source_code/game_objects/pig_classes/free_pig.h \
    source_code/game_objects/pig_classes/shot_pig.h \
    source_code/utils/animation.h \
    source_code/utils/constants.h \
    source_code/utils/resource_storage.h \
    source_code/utils/sound_player.h \
    source_code/utils/utils.h \
    source_code/view_controller/field_controller.h \
    source_code/view_controller/field_view.h \
    source_code/view_controller/main_window.h \

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    textures/sand/middle_block.png \
    textures/sand/right_block.png
