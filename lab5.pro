#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T17:15:33
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab5
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    userwindow.cpp \
    setlevel.cpp \
    auth.cpp \
    adminrights.cpp

HEADERS  += mainwindow.h \
    settings.h \
    userwindow.h \
    setlevel.h \
    auth.h \
    adminrights.h

FORMS    += mainwindow.ui \
    settings.ui \
    userwindow.ui \
    setlevel.ui \
    auth.ui \
    adminrights.ui
