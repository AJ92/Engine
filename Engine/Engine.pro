#-------------------------------------------------
#
# Project created by QtCreator 2013-11-25T19:06:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Engine
TEMPLATE = app

INCLUDEPATH += Math

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
    Graphics/Model/model.cpp \
    Graphics/Model/Components/mesh.cpp \
    Graphics/Model/Components/material.cpp \
    Graphics/Model/Parser/loader.cpp \
    Graphics/Model/Parser/Format_obj/loader_obj.cpp \
    Math/Vector/vector4.cpp \
    Math/Vector/vector3.cpp \
    Math/Matrix/matrix4x4.cpp \
    Math/Matrix/matrix3x3.cpp \
    Graphics/Shader/shader.cpp \
    Graphics/Camera/camera.cpp \
    Graphics/Model/modellibrary.cpp \
    Event/Events/eventdebugger.cpp \
    Graphics/Model/Streamer/streamToDisk.cpp \
    Graphics/Model/Streamer/streamer.cpp \
    Threading/threadaccountant.cpp \
    Graphics/Procedural/planet.cpp \
    Graphics/Procedural/planetlod.cpp \
    Graphics/Procedural/planetgenerator.cpp \
    Graphics/Model/materiallibrary.cpp \
    Event/Events/eventstreamer.cpp \
    Input/keyboard.cpp \
    Input/mouse.cpp

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
    Graphics/Model/model.h \
    Graphics/Model/Components/mesh.h \
    Graphics/Model/Components/material.h \
    Graphics/Model/Parser/loader.h \
    Graphics/Model/Parser/Format_obj/loader_obj.h \
    Math/Vector/vector4.h \
    Math/Vector/vector3.h \
    Math/Matrix/matrix4x4.h \
    Math/Matrix/matrix3x3.h \
    Graphics/OpenGL/OpenGL.h \
    Math/mathematics.h \
    Graphics/Shader/shader.h \
    Graphics/Camera/camera.h \
    Graphics/Model/modellibrary.h \
    Event/Events/eventdebugger.h \
    Graphics/Model/Streamer/streamToDisk.h \
    Graphics/Model/Streamer/streamer.h \
    Threading/threadaccountant.h \
    Graphics/Procedural/planet.h \
    Graphics/Procedural/planetlod.h \
    Graphics/Procedural/planetgenerator.h \
    Graphics/Model/materiallibrary.h \
    Event/Events/eventstreamer.h \
    Input/keyboard.h \
    Input/mouse.h

FORMS    += \
    Debug/Ui/debugwindow.ui


windows: {
    message(Windows desktop build mingw 32 bit)
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
