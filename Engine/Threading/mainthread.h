#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QThread>
#include <QWaitCondition>
#include <QMutexLocker>
#include <QMutex>
#include <QString>

//This has to stay above freeglut include!!!
#include "Graphics/Renderer/renderer.h"
#include "Graphics/Window/window.h"
#include "Graphics/OpenGL/OpenGL.h"


#include "Event/eventlistener.h"
#include "Event/eventtransmitter.h"


#include "Graphics/Model/modellibrary.h"

#include "engine.h"
//forward declaration...
class Engine;


class MainThread : public QThread , virtual public EventListener, virtual public EventTransmitter
{
    Q_OBJECT
public:
    MainThread(Engine * parent, Window * w);
    ~MainThread();

    void init();

    void start_mainThread();
    void stop_mainThread();


    //callbacks
    void keyboard(unsigned char key, int x, int y);
    void idle();
    void timer(int value);
    void render();

    //temprary
    void setModels(ModelLibrary modellib);



protected:
    void run();

private:
    QMutex mutex;
    QWaitCondition condition;
    bool running;
    bool abort;

    //FPS settings
    int frame_count;
    int fps;

    //Renderer
    Renderer *r;

    //Engine
    Engine *parent;

    //Window
    Window *w;

    void eventRecieved(Event e);
    void debugMessage(QString message);


    //temprary
    ModelLibrary model_library;
};

#endif // MAINTHREAD_H
