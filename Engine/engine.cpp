#include "engine.h"

/*!
  Main class.
  Manages all the crazy stuff an engine needs to manage.

  This is actually a wrapper for all the other stuff like
  window management... renderer... physics and god knows what else...
  */





// C part (CALLBACKS AND GLOBAL POINTER)
Engine * ptr_global_engine_instance = NULL;

void render_callback(void);
void error_callback(int error, const char* description);

//void keyboard_callback(unsigned char key, int x, int y);


void render_callback(void){
    ptr_global_engine_instance->render();
}

void error_callback(int error, const char* description){
    ptr_global_engine_instance->error(error,description);
}


/*
void keyboard_callback(unsigned char key, int x, int y){
    ptr_global_engine_instance->keyboard(key, x, y);
}
*/
// C part END





/*!
  Sets on object creation the pointer for the C callback wrapper.
  */
Engine::Engine(QObject *parent) :
    EventListener(),
    EventTransmitter(),
    QObject(parent)
{
    //set global pointer for callbacks
    ptr_global_engine_instance = this;

    running = false;

    debug_visible = false;
    frame_count = 0;
    fps = 0;

    //lighttime = 0;

    idealThreadCount = 1;

    //init debugger and it's listener

    debugger = new Debugger();
    debuggerListener = debugger;
    addListener(debuggerListener);

    debugMessage("engine created.");


    //creating the window
    window = new Window();
    //listener has to be set before initialization for debug output.
    windowTransmitter = window;
    windowTransmitter->addListener(debuggerListener);

    debugMessage("Ideal thread number: " + QString::number(QThread::idealThreadCount()));
    idealThreadCount = QThread::idealThreadCount();

    //-1 == keep mainthread free
    threadAccountant = new ThreadAccountant(idealThreadCount);


    app_dir = QApplication::applicationDirPath();
    debugMessage("Application Dir: " + app_dir);

    if(QElapsedTimer::clockType() == QElapsedTimer::PerformanceCounter){
        debugMessage("PerformanceTimer in use");
    }



    //loads models
    //we do not init it cause ObjectWorld does this for us...
    model_loader = new ModelLoader(threadAccountant);
    model_loader->addListener(debuggerListener);

    //our world with all the fancy objects...
    object_world = SP<ObjectWorld>(new ObjectWorld(threadAccountant));
    object_world->addListener(debuggerListener);
    object_world->setModelLoader(model_loader);
    object_world->setLightModelPath(getApplicationDir() + "//light_sphere.obj");
    object_world->setUnitCubeModelPath(getApplicationDir() + "//cube.obj");


    //create keyboard
    k = new KeyBoard(window);
    k->addListener(debuggerListener);

    //create mouse
    m = new Mouse(window);
    m->addListener(debuggerListener);

    //create renderer
    r = new Renderer();
    r->addListener(debuggerListener);

    //create default cam
    cam = new Camera();


    t = new QTimer(this);
    //1000 ms / 60 fps = 16.6 ms/second
    //16 makes some high cpu usage
    //17 is just fina actually but only 59 fps
    t->setInterval(16);

    frameTime = 0;
    time = 0;
    //deltatime in ns (16 ms)
    deltaTime = 1000000000/60;
    accumulator = 0;
    timestep = 1.0f;



    fps_timer = new QTimer(this);
    fps_timer->setInterval(1000);
}

Engine::~Engine(){
    running = false;
    glfwTerminate();
    qDebug("engine stopped.");

    //need to delete remaining rawpointers here...
}

/*!
  If everything is set up, this command starts the engine.
  */
void Engine::initialize(int argc, char *argv[]){
    debugMessage("engine initializing...");

    //GLEW
    GLenum GlewInitResult;

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwSetErrorCallback(error_callback);



    //CONNECT RESIZE EVENT HERE
    window->initialize();


    //GLEW
    glewExperimental = GL_TRUE;
    GlewInitResult = glewInit();
    if (GLEW_OK != GlewInitResult) {
        debugMessage("ERROR (2): " + QString((char*)glewGetErrorString(GlewInitResult)));
        exit(EXIT_FAILURE);
    }

    //Debugging OpenGL info...
    debugMessage("INFO: OpenGL Version: " + QString((char*)glGetString(GL_VERSION)));
    debugMessage("INFO: OpenGL Vendor: " + QString((char*)glGetString(GL_VENDOR)));
    debugMessage("INFO: OpenGL Renderer: " + QString((char*)glGetString(GL_RENDERER)));
    debugMessage("INFO: OpenGL Shading Language version: " + QString((char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));





    //init modelloader and objectworld... octrees n stuff...
    object_world->initialize();


    //init keyboard
    k->initialize();
    window->registerKeyboard(k);

    //init mouse
    m->initialize();
    window->registerMouse(m);


    //init renderer
    r->initialize();
    r->setPolygonMode(Renderer::PolygonModeStandard);
    r->setCamera(cam);
    r->setWindow(window);


    //set default gl stuff
    glClearColor(0.5f,0.5f,0.5f,1.0f); //grey


    debugMessage("starting main event timer...");
    running = true;

    //here the "main 'thread' starts
    QObject::connect(t,SIGNAL(timeout()),this,SLOT(eventLoop()));
    elapseTimer.start();
    t->start();


    QObject::connect(fps_timer,SIGNAL(timeout()),this,SLOT(timer()));
    fps_timer->start();
    debugMessage("engine initialized.");
}

void Engine::setWindowTitle(QString title){
    if(running){
        window->setWindowTitle(title);
    }
}

void Engine::showDebugWindow(){
    qDebug("...");
    if(!debug_visible){
        Event e;
        e.type = Event::EventDebuggerShow;
        this->transmit(e);
        debug_visible = true;
    }
    qDebug("... ...");
}

void Engine::hideDebugWindow(){
    if(debug_visible){
        Event e;
        e.type = Event::EventDebuggerHide;
        this->transmit(e);
        debug_visible = false;
    }
}

void Engine::setWindowSize(int width, int height){
    if(running){
        window->setWindowSize(width, height);
    }
}

int Engine::getWindowWidth(){
    if(running){
        return window->getWindowWidth();
    }
    return -1;
}

int Engine::getWindowHeight(){
    if(running){
        return window->getWindowHeight();
    }
    return -1;
}

QString Engine::getApplicationDir(){
    return app_dir;
}

Camera* Engine::getCamera(){
    return cam;
}

double Engine::getTimeStep(){
    return timestep;
}

bool Engine::isRunning(){
    return running;
}

int Engine::getFps(){
    return fps;
}

//simple fps calc
void Engine::timer(){
    //fps = frame_count;

    frame_count = 0;

    Event e;
    e.type = Event::EventDebuggerFPS;
    e.debugger = new EventDebugger(fps);
    this->transmit(e);

    Event e2;
    e2.type = Event::EventDebuggerNSPerFrame;
    e2.debugger = new EventDebugger(frameTime);
    this->transmit(e2);

    Event e3;
    e3.type = Event::EventDebuggerMeshsPerFrame;
    e3.debugger = new EventDebugger(r->getMeshPerFrameCount());
    this->transmit(e3);

    Event e4;
    e4.type = Event::EventDebuggerTrianglesPerFrame;
    e4.debugger = new EventDebugger(r->getTrianglesPerFrameCount());
    this->transmit(e4);

    Event e5;
    e5.type = Event::EventDebuggerTimeStep;
    e5.debugger = new EventDebugger(timestep);
    this->transmit(e5);

    Event e6;
    e6.type = Event::EventDebuggerTexBindsPerFrame;
    e6.debugger = new EventDebugger(r->getTexBindsPerFrameCount());
    this->transmit(e6);


}


void Engine::render()
{
    frame_count++;

    //timer timestep and so on...
    frameTime = elapseTimer.nsecsElapsed();
    elapseTimer.restart();

    fps = int(1000000000 / frameTime);

    //max frame time to avoid spiral of death
    //all values in nanosecs (1 ms = 1 000 000 ns)
    if(frameTime > 100000000){
        frameTime = 100000000;
    }
    if(frameTime < 10000000){
        frameTime = 10000000;
    }
    /*
    accumulator += frameTime;
    time = 0;
    while (accumulator >= deltaTime){
        time += deltaTime;
        accumulator -= deltaTime;
        //simulation here...
    }
    */
    timestep = (double)frameTime/(double)deltaTime;


    //render every model
    /*
    if(model_library->modelCount() > 0){
        QList<Model *> model_list = model_library->getModels();
        QList<Model *>::iterator i;
        for (i = model_list.begin(); i != model_list.end(); ++i){
            Model * m = *i;
            r->render(m);
        }
    }
    */

    if(!glfwWindowShouldClose(window->getGLFWwindow()))
    {

        //render the mdllib
        //forget about the next 2...
        //r->setModelLibrary(model_library);
        //r->setLightLibrary(light_library);

        //set the objectworld
        r->setObjectWorld(object_world);

        r->render_v2();

        //glutSwapBuffers();
        //glutPostRedisplay();

        glfwSwapBuffers(window->getGLFWwindow());
        glfwPollEvents();


    }
    else{
        //window gets closed
        qDebug("window closed by user");
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }

}

void Engine::error(int error, const char* description){
    debugMessage("GLWF Error (" + QString::number(error) + "): " + QString(description));
}

void Engine::setClearColor(float r, float g, float b, float a){
    //dont want to check for good values... user should do it
    glClearColor(r,g,b,a);
}

void Engine::eventCall(){

}

//SLOTS
void Engine::eventLoop(){
    eventCall();
    render();
}

//dynamic light
SP<CompositeObject> Engine::loadLightObject(QString name){
    return object_world->loadLightobject(name);
}

//dynamic
SP<CompositeObject> Engine::loadModelObject(QString name, QString path){
    return object_world->loadModelobject(name, path);
}

//static
SP<CompositeObject> Engine::loadModelObject(QString name, QString path, SP<Positation> posi){
    return object_world->loadModelobject(name, path, posi);
}

void Engine::setCamera(Camera * cam){
    this->cam = cam;
    r->setCamera(this->cam);
}
