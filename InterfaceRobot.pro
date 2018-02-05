#-------------------------------------------------
#
# Project created by QtCreator 2017-12-30T13:43:43
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InterfaceRobot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mygraphicsscene.cpp \
    mymap.cpp

HEADERS  += mainwindow.h \
    mygraphicsscene.h \
    mymap.h

FORMS    += mainwindow.ui

RESOURCES += \
    imagens.qrc
