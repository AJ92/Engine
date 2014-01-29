#ifndef ENGINE_H
#define ENGINE_H


#include <QObject>
#include <QString>

#include "Event/eventtransmitter.h"

#include "Debug/Ui/debugwindow.h"
#include "Debug/debugger.h"

// OpenGL.h
// #include "Graphics/glew/include/GL/glew.h"
// #include "Graphics/freeglut/include/GL/freeglut.h"

#include "Graphics/OpenGL/OpenGL.h"
#include "Graphics/Renderer/renderer.h"
#include "Graphics/Window/window.h"

#include "Graphics/Model/Streamer/streamer.h"

#include "Graphics/Model/modellibrary.h"
#include "Graphics/Model/model.h"

#include <QTimer>
#include <QThread>

#include "Threading/threadaccountant.h"



class Engine : public QObject, virtual public EventListener, virtual public EventTransmitter
{

    Q_OBJECT

public:
    explicit Engine(QObject *parent = 0);
    ~Engine();
    void initialize(int argc, char *argv[]);


    //WINDOW
    void setWindowTitle(QString title);
    void setWindowSize(int width, int height);
    int getWindowWidth();
    int getWindowHeight();

    bool isRunning();

    void showDebugWindow();
    void hideDebugWindow();

    void debugMessage(QString message);



    int getFps();




    //RENDER

    //callbacks
    void keyboard(unsigned char key, int x, int y);
    void idle();
    void timer(int value);
    void render();





    //temprary model loader test
    //needs to be redirected and synced over threads...

    Model * loadModel(QString path);

private:

    bool running;


    //window settings
    EventTransmitter * windowTransmitter;
    Window * window;

    //renderer
    Renderer *r;

    //FPS settings
    int frame_count;
    int fps;


    //Timer for glut event loop
    QTimer * t;


    //Debug settings
    //this is actually a Debug window but hidden behind an EventListener
    EventListener * debuggerListener;
    Debugger * debugger;
    bool debug_visible;


    //model loader and threads.
    ModelLibrary * model_library;

    int idealThreadCount;
    ThreadAccountant * threadAccountant;


    //thread stuff...
    void transferModelsToMainThread();

public slots:
    void eventLoop();

};

#endif // ENGINE_H
