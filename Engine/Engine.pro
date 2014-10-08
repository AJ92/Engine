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
    Math/Geometry/plane.cpp\
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
    Math/Intersections/intersections.cpp \
    Math/Geometry/aabb.cpp \
    Math/Geometry/sphere.cpp



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
    Math/Geometry/plane.h \
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
    Math/Intersections/intersections.h \
    Math/Geometry/aabb.h \
    Math/Geometry/sphere.h



FORMS    += \
    Debug/Ui/debugwindow.ui


windows: {
    message(Windows desktop build mingw 32 bit)



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





    #BULLET PHYSICs
    INCLUDEPATH += Physics/bullet-2.82-r2704/src
    DEPENDPATH += Physics/bullet-2.82-r2704/src

    LIBS += -L$$_PRO_FILE_PWD_/Physics/bullet-2.82-r2704/lib
    CONFIG(release, debug|release): LIBS += -lBulletCollision_Debug -lBulletDynamics_Debug -lBulletSoftBody_Debug -lLinearMath_Debug
    CONFIG(debug, debug|release): LIBS += -lBulletCollision_Debug -lBulletDynamics_Debug -lBulletSoftBody_Debug -lLinearMath_Debug


    message($$INCLUDEPATH)
    message($$LIBS)
}
