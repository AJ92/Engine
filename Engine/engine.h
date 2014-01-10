#ifndef ENGINE_H
#define ENGINE_H

#include <QString>

#include "Event/eventtransmitter.h"

#include "Debug/Ui/debugwindow.h"
#include "Debug/debugger.h"

// OpenGL.h
// #include "Graphics/glew/include/GL/glew.h"
// #include "Graphics/freeglut/include/GL/freeglut.h"

#include "Graphics/OpenGL/OpenGL.h"

#include "Graphics/Window/window.h"

#include "Threading/mainthread.h"
#include "Threading/streamthread.h"


#include "Graphics/Model/modellibrary.h"
#include "Graphics/Model/Parser/loader.h"
#include "Graphics/Model/model.h"




class Engine : virtual public EventListener, virtual public EventTransmitter
{
public:
    Engine();
    ~Engine();
    void initialize(int argc, char *argv[]);


    void setWindowTitle(QString title);
    void setWindowSize(int width, int height);
    int getWindowWidth();
    int getWindowHeight();

    bool isRunning();

    void showDebugWindow();
    void hideDebugWindow();

    int getFps();

    void debugMessage(QString message);

    //temprary model loader test
    //needs to be redirected and synced over threads...

    Model loadModel(QString path);

private:

    bool running;

    EventTransmitter * mainThreadTransmitter;
    MainThread * mainThread;

    EventTransmitter * streamThreadTransmitter;
    StreamThread * streamThread;


    //window settings
    EventTransmitter * windowTransmitter;
    Window * window;


    //Debug settings
    //this is actually a Debug window but hidden behind an EventListener
    EventListener * debuggerListener;
    Debugger * debugger;
    bool debug_visible;

    //FPS settings
    int frame_count;
    int fps;




    //temprary model loader test...
    //will be outsourced into streaming thread ...
    Loader model_loader;
    ModelLibrary model_library;

    //thread stuff...
    void transferModelsToMainThread();

};

#endif // ENGINE_H
