#ifndef ENGINE_H
#define ENGINE_H

#include <QString>

#include "Event/eventtransmitter.h"

#include "Debug/Ui/debugwindow.h"
#include "Debug/debugger.h"

#include "Graphics/glew/include/GL/glew.h"
#include "Graphics/freeglut/include/GL/freeglut.h"

#include "Graphics/Window/window.h"



class Engine : public EventTransmitter
{
public:
    Engine();
    void initialize(int argc, char *argv[]);

    void keyboard(unsigned char key, int x, int y);
    void idle();
    void timer(int value);
    void render();


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
