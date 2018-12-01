#-------------------------------------------------
#
# Project created by QtCreator 2018-11-05T23:17:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QReversi
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

SOURCES += \
        main.cc \
    core/players/ai.cc \
    core/players/human.cc \
    core/players/virtualplayer.cc \
    core/battle.cc \
    core/gameplay.cc \
    ui/mainwindow.cc \
    ui/checkerboard/boardlayout.cc \
    ui/checkerboard/checkerboardwidget.cc \
    ui/checkerboard/boardgrid.cc \
    ui/newgamedialog.cc

HEADERS += \
    ui/mainwindow.h \
    ui/checkerboard/boardlayout.h \
    ui/checkerboard/checkerboardwidget.h \
    core/players/ai.h \
    core/players/human.h \
    core/players/virtualplayer.h \
    core/battle.h \
    core/gameplay.h \
    ui/checkerboard/boardgrid.h \
    ui/newgamedialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ui/newgamedialog.ui

RESOURCES += \
    resources.qrc
