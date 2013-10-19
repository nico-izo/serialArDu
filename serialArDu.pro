#-------------------------------------------------
#
# Project created by QtCreator 2013-10-06T12:50:45
#
#-------------------------------------------------

QT       += core gui widgets
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serialArDu
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    terminal.cpp \
    commandinput.cpp \
    ardusettings.cpp \
    wasdinput.cpp

HEADERS  += mainwindow.h \
    terminal.h \
    commandinput.h \
    ardusettings.h \
    wasdinput.h

FORMS    += mainwindow.ui \
    ardusettings.ui
