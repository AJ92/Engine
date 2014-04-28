#ifndef ENGINE_H
#define ENGINE_H

#define GLFW_DLL

#include <QObject>
#include <QString>
#include <QList>

#include "Event/eventtransmitter.h"

#include "Debug/Ui/debugwindow.h"
#include "Debug/debugger.h"

#include "Graphics/OpenGL/OpenGL.h"
#include "Graphics/Renderer/renderer.h"
#include "Graphics/Window/window.h"
#include "Input/keyboard.h"
#include "Input/mouse.h"

#include "Graphics/Model/Streamer/streamer.h"

#include "Graphics/Model/modellibrary.h"
#include "Graphics/Model/model.h"

#include "Graphics/Model/lightlibrary.h"
#include "Graphics/Model/light.h"

#include <QApplication>
#include <QElapsedTimer>
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

    int getFps();




    //RENDER

    //callbacks
    void render();
    void error(int error, const char* description);

    //some functions
    void setClearColor(float r, float g, float b, float a);


    //KEYBOARD (override if needed)
    //void keyFunction();


    //temporary model loader test
    //needs to be redirected and synced over threads...

    Model * loadModel(QString path);
    Light * loadLight(QString path);
    void setCamera(Camera * cam);

    QString getApplicationDir();

    Camera* getCamera();
    double getTimeStep();


private:

    //test values
    Camera * cam;
    //test values end

    bool running;

    //APP stuff
    QString app_dir;

    //window settings
    EventTransmitter * windowTransmitter;
    Window * window;

protected:
    //renderer
    Renderer *r;

    //keyboard
    KeyBoard *k;

    //Mouse
    Mouse *m;

    //model loader and threads.
    ModelLibrary * model_library;

    //light loader and threads.
    LightLibrary * light_library;


private:


    //FPS settings
    int frame_count;
    int fps;

    //timesteps
    double timestep;
    qint64 frameTime;
    qint64 time;
    qint64 deltaTime;
    qint64 accumulator;

    QElapsedTimer elapseTimer;


    //Timer for glut event loop
    QTimer * t;
    QTimer * fps_timer;


    //Debug settings
    //this is actually a Debug window but hidden behind an EventListener
    EventListener * debuggerListener;
    Debugger * debugger;
    bool debug_visible;



    int idealThreadCount;
    ThreadAccountant * threadAccountant;


    ///////
    // DEBUG STUFF
    // TESTING MATRICES

    //Model * cam_test;


    virtual void eventCall();


public slots:
    void eventLoop();
    void timer();

};

#endif // ENGINE_H
