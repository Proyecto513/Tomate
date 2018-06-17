#-------------------------------------------------
#
# Project created by QtCreator 2018-06-09T22:39:51
#
#-------------------------------------------------

QT       += core gui multimedia dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = tomate
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

include(src/third-party/singleapplication/singleapplication.pri)
DEFINES += QAPPLICATION_CLASS=QApplication

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
CONFIG += c++11

SOURCES += \
        src/main.cpp \
        src/trayicon.cpp \
        src/timer.cpp \
        src/settings.cpp \
    src/notification.cpp

HEADERS += \
        src/trayicon.h \
        src/timer.h \
        src/settings.h \
    src/notification.h

FORMS += \
    src/settings.ui

RESOURCES += \
    src/assets.qrc
