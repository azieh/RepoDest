#-------------------------------------------------
#
# Project created by QtCreator 2015-10-26T20:48:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = RepoDest
TEMPLATE    = app

CONFIG      += c++11

SOURCES     += \
                main.cpp\
                mainwindow.cpp \
                client.cpp \
                core/snap7.cpp

LIBS        += -L"$(MINGW)/lib" -static-libgcc c:\lib\snap7.lib

HEADERS     += \
                mainwindow.h \
                client.h \
                core/snap7.h

FORMS       += mainwindow.ui

DISTFILES   += \
                core/snap7.lib \
                core/snap7.dll

RESOURCES += \
    ico.qrc
