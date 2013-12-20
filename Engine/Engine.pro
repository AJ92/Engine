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
    Debug/Ui/debugwindow.cpp \
    engine.cpp \
    Event/event.cpp \
    Event/eventlistener.cpp \
    Event/eventtransmitter.cpp \
    Debug/debugger.cpp \
    Graphics/Window/window.cpp \
    Graphics/Renderer/renderer.cpp \
    Threading/mainthread.cpp \
    Threading/streamthread.cpp

HEADERS  += \
    Object/object.h \
    Debug/Ui/debugwindow.h \
    engine.h \
    Event/event.h \
    Event/eventlistener.h \
    Event/eventtransmitter.h \
    Debug/debugger.h \
    Graphics/Window/window.h \
    Graphics/Renderer/renderer.h \
    Threading/mainthread.h \
    Threading/streamthread.h

FORMS    += \
    Debug/Ui/debugwindow.ui


windows: {
    message(Windows desktop build)
    #OPEN GL

    #not shure if needed but might come in handy
    QT += opengl



    LIBS += -lopengl32

    #freeGLUT
    INCLUDEPATH += Graphics/freeglut/include
    DEPENDPATH += Graphics/freeglut/include

    LIBS += -L$$_PRO_FILE_PWD_/Graphics/freeglut/lib
    CONFIG(release, debug|release): LIBS += -lfreeglut
    CONFIG(debug, debug|release): LIBS += -lfreeglut


    #GLEW
    INCLUDEPATH += Graphics/glew/include
    DEPENDPATH += Graphics/glew/include

    LIBS += -L$$_PRO_FILE_PWD_/Graphics/glew/lib
    CONFIG(release, debug|release): LIBS += -lglew32
    CONFIG(debug, debug|release): LIBS += -lglew32


    message($$INCLUDEPATH)
    message($$LIBS)
}
