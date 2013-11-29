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


windows: {
    message(Windows desktop build)
    #OPEN GL

    #not shure if needed but might come in handy
    QT += opengl

    INCLUDEPATH += Graphics/freeglut/include
    DEPENDPATH += Graphics/freeglut/include


    LIBS += -lopengl32

    #freeGLUT

    LIBS += -L$$_PRO_FILE_PWD_/Graphics/freeglut/lib
    CONFIG(release, debug|release): LIBS += -lfreeglut
    CONFIG(debug, debug|release): LIBS += -lfreeglut

    message($$INCLUDEPATH)
    message($$LIBS)
}
