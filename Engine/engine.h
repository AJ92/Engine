#ifndef ENGINE_H
#define ENGINE_H


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
    //moved to own class KeyBoard
    //void keyboard(unsigned char key, int x, int y);
    void idle();
    void timer(int value);
    void render();

    //some functions
    void setClearColor(float r, float g, float b, float a);


    //KEYBOARD (override if needed)
    void keyFunction();


    //temprary model loader test
    //needs to be redirected and synced over threads...

    Model * loadModel(QString path);
    Light * loadLight(QString path);
    void setCamera(Camera * cam);

    QString getApplicationDir();


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

    //renderer
    Renderer *r;

    //keyboard
    KeyBoard *k;

    //Mouse
    Mouse *m;
    double x_angle;
    double y_angle;


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


    //Debug settings
    //this is actually a Debug window but hidden behind an EventListener
    EventListener * debuggerListener;
    Debugger * debugger;
    bool debug_visible;


    //model loader and threads.
    ModelLibrary * model_library;

    //light loader and threads.
    LightLibrary * light_library;

    QList<Light*> lights;
    double lighttime;

    int idealThreadCount;
    ThreadAccountant * threadAccountant;




    ///////
    // DEBUG STUFF
    // TESTING MATRICES

    Model * cam_test;




public slots:
    void eventLoop();

};

#endif // ENGINE_H
