#ifndef ENGINE_H
#define ENGINE_H

#include <QString>

#include "Event/eventtransmitter.h"

#include "Debug/Ui/debugwindow.h"
#include "Debug/debugger.h"

#include "Graphics/glew/include/GL/glew.h"
#include "Graphics/freeglut/include/GL/freeglut.h"

#include "Graphics/Window/window.h"

#include "Threading/mainthread.h"




class Engine : public EventTransmitter
{
public:
    Engine();
    void initialize(int argc, char *argv[]);


    void setWindowTitle(QString title);
    void setWindowSize(int width, int height);
    int getWindowWidth();
    int getWindowHeight();


    void showDebugWindow();
    void hideDebugWindow();

    int getFps();

    void debugMessage(QString message);

private:

    bool running;

    EventTransmitter * mainThreadTransmitter;
    MainThread * mainThread;


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

};

#endif // ENGINE_H
