#-------------------------------------------------
#
# Project created by QtCreator 2013-11-25T19:06:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Engine
TEMPLATE = app


SOURCES += main.cpp\
    Object/object.cpp \
    Debug/Ui/debugwindow.cpp

HEADERS  += \
    Object/object.h \
    Debug/Ui/debugwindow.h

FORMS    += \
    Debug/Ui/debugwindow.ui
