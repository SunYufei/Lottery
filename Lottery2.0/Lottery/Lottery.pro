#-------------------------------------------------
#
# Project created by QtCreator 2016-04-14T11:53:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lottery
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    titlebar.cpp

HEADERS  += mainwindow.h \
    titlebar.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc

RC_FILE = \
    icon.rc

DISTFILES += \
    icon.rc
