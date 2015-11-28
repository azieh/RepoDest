#-------------------------------------------------
#
# Project created by QtCreator 2015-10-26T20:48:37
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = RepoDest
TEMPLATE    = app

CONFIG      += c++11
QTPLUGIN    += qsqloci

SOURCES     +=  main.cpp\
                mainwindow.cpp \
                core/snap7.cpp \
                workarea.cpp \
                threadmanager.cpp \
                sqlhandler.cpp \
                plchandler.cpp

LIBS        += -L"$(MINGW)/lib" "C:\lib\snap7.lib"

HEADERS     +=  mainwindow.h \
                core/snap7.h \
                workarea.h \
                threadmanager.h \
                sqlhandler.h \
                plchandler.h

FORMS       +=  mainwindow.ui

DISTFILES   +=  core/snap7.lib \
                core/snap7.dll

RESOURCES   +=  ico.qrc

RC_FILE     =   RepoDest.rc
