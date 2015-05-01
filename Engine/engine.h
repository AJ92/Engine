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

#include "Graphics/Model/modelloader.h"
#include "Graphics/World/objectworld.h"

#include "Graphics/Model/modellibrary.h"
#include "Graphics/Model/model.h"

#include "Graphics/Model/light.h"

#include <QApplication>
#include <QElapsedTimer>
#include <QTimer>
#include <QThread>

#include "Threading/threadaccountant.h"

#include "Graphics/World/DataStructure/octtree.h"


#include "Physics/Physics.h"

#include "Object/compositeobject.h"

#include "Object/SmartPointer/sp.h"

#include "Event/event.h"

#include "Object/positation.h"




class Event;
class Positation;
class Entity;
class EntityManager;

namespace QE
{
    class Engine : public QObject, virtual public EventListener, virtual public EventTransmitter
    {

        Q_OBJECT

    public:
        explicit Engine(QObject *parent = 0);
        ~Engine();
        void initialize(int argc, char *argv[]);



        bool isRunning();

        void showDebugWindow();
        void hideDebugWindow();

        int getFps();




        //RENDER

        //callbacks
        //called to update the timer and stuff...
        void update();
        void error(int error, const char* description);

        //some functions
        void setClearColor(float r, float g, float b, float a);


        //KEYBOARD (override if needed)
        //void keyFunction();

        /*
        SP<CompositeObject> loadLightObject(QString name);
        SP<CompositeObject> loadModelObject(QString name, QString path);
        SP<CompositeObject> loadModelObject(QString name, QString path, SP<Positation> posi);
        */

        SP<Entity> loadLightObjectE(QString name);
        SP<Entity> loadModelObjectE(QString name, QString path);
        SP<Entity> loadModelObjectE(QString name, QString path, SP<Positation> posi);



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



    protected:
        //window
        Window * window;
        //renderer
        Renderer *r;
        //keyboard
        KeyBoard *k;
        //Mouse
        Mouse *m;

        //model loader and threads.
        //ModelLibrary * model_library;

        //light loader and threads.
        //LightLibrary * light_library;



        ModelLoader * model_loader;
        EntityManager * entity_manager;
        //holds all objects ... soooooon...
        SP<ObjectWorld> object_world;


    private:


        //FPS settings
        int frame_count;
        int fps;

        //timesteps
        double timestep;
        double framestep;
        qint64 frameTime;
        qint64 time;
        qint64 deltaTime;
        double accumulator;
        double frameSlice;


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


        //called during the main loop
        virtual void eventCall(double fs);


        //renders a frame
        void render();


    public slots:
        void eventLoop();
        void timer();

    };
}

#endif // ENGINE_H
