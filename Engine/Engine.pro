#-------------------------------------------------
#
# Project created by QtCreator 2013-11-25T19:06:38
#
#-------------------------------------------------


#------minor modifications------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Engine
TEMPLATE = app

#----------C++11------------
QMAKE_CXXFLAGS += -std=c++0x

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
    Event/Events/eventstreamer.cpp \
    Input/keyboard.cpp \
    Input/mouse.cpp \
    Graphics/Model/light.cpp \
    Event/Events/eventwindow.cpp \
    Graphics/Camera/frustum.cpp \
    test.cpp \
    Graphics/World/objectworld.cpp \
    Graphics/World/DataStructure/octtree.cpp \
    Graphics/Model/modelloader.cpp \
    Event/Events/eventmodel.cpp \
    Object/compositeobject.cpp \
    Object/positation.cpp \
    Event/Events/eventcompositeobject.cpp \
    Debug/Ui/customgraph.cpp \
    Graphics/World/DataStructure/octtreefast.cpp \
    Object/SmartPointer/sp.cpp \
    Object/SmartPointer/referencecounter.cpp \
    Graphics/Model/Parser/Format_assimp/loader_assimp.cpp \
    Graphics/Model/Components/texturemap.cpp \
    Graphics/Model/Components/texturemapcube.cpp \
    Object/component.cpp \
    Object/entity.cpp \
    Object/entitymanager.cpp



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
    Graphics/OpenGL/OpenGL.h \
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
    Event/Events/eventstreamer.h \
    Input/keyboard.h \
    Input/mouse.h \
    Graphics/Model/light.h \
    Event/Events/eventwindow.h \
    Graphics/Camera/frustum.h \
    test.h \
    Physics/Physics.h \
    Graphics/World/objectworld.h \
    Graphics/World/DataStructure/octtree.h \
    Graphics/Model/modelloader.h \
    Event/Events/eventmodel.h \
    Object/compositeobject.h \
    Object/positation.h \
    Event/Events/eventcompositeobject.h \
    Debug/Ui/customgraph.h \
    Graphics/World/DataStructure/octtreefast.h \
    Object/SmartPointer/sp.h \
    Object/SmartPointer/referencecounter.h \
    Object/SmartPointer/smartpointer.h \
    Graphics/Model/Parser/Format_assimp/loader_assimp.h \
    Graphics/Model/Components/texturemap.h \
    Graphics/Model/Components/texturemapcube.h \
    Object/component.h \
    Object/entity.h \
    Object/entitymanager.h \
    Object/CompositionHelper.h



FORMS    += \
    Debug/Ui/debugwindow.ui


windows: {
    message(Windows desktop build mingw 32 bit)




    #Mathematics lib
    DEPENDPATH  +=  Math/lib
    INCLUDEPATH +=  Math/include
    LIBS += -L$$_PRO_FILE_PWD_/Math/lib
    CONFIG(release, debug|release): LIBS += -lMathematics
    CONFIG(debug, debug|release): LIBS += -lMathematics


    #GLFW
    INCLUDEPATH += Graphics/glfw/include
    DEPENDPATH += Graphics/glfw/include
    LIBS += -L$$_PRO_FILE_PWD_/Graphics/glfw/lib-mingw
    CONFIG(release, debug|release): LIBS += -lglfw3dll
    CONFIG(debug, debug|release): LIBS += -lglfw3dll


    #OPEN GL

    #not shure if needed but might come in handy
    QT += opengl


    LIBS += -lopengl32

    #freeGLUT
    #INCLUDEPATH += Graphics/freeglut/include
    #DEPENDPATH += Graphics/freeglut/include
    #LIBS += -L$$_PRO_FILE_PWD_/Graphics/freeglut/lib
    #CONFIG(release, debug|release): LIBS += -lfreeglut
    #CONFIG(debug, debug|release): LIBS += -lfreeglut



    #GLEW
    INCLUDEPATH += Graphics/glew/include
    DEPENDPATH += Graphics/glew/include

    LIBS += -L$$_PRO_FILE_PWD_/Graphics/glew/lib
    CONFIG(release, debug|release): LIBS += -lglew32
    CONFIG(debug, debug|release): LIBS += -lglew32


    #ASSIMP
    INCLUDEPATH += Graphics/assimp/include
    DEPENDPATH += Graphics/assimp/include

    LIBS += -L$$_PRO_FILE_PWD_/Graphics/assimp/lib
    CONFIG(release, debug|release): LIBS += -lassimp
    CONFIG(debug, debug|release): LIBS += -lassimp



    #BULLET PHYSICs
    INCLUDEPATH += Physics/bullet-2.82-r2704/src
    DEPENDPATH += Physics/bullet-2.82-r2704/src

    LIBS += -L$$_PRO_FILE_PWD_/Physics/bullet-2.82-r2704/lib
    CONFIG(release, debug|release): LIBS += -lBulletCollision_Debug -lBulletDynamics_Debug -lBulletSoftBody_Debug -lLinearMath_Debug
    CONFIG(debug, debug|release): LIBS += -lBulletCollision_Debug -lBulletDynamics_Debug -lBulletSoftBody_Debug -lLinearMath_Debug


    message($$INCLUDEPATH)
    message($$LIBS)
}
