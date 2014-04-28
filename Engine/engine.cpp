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
}

Engine::~Engine(){
    running = false;
    glfwTerminate();
    qDebug("engine stopped.");
}

/*!
  If everything is set up, this command starts the engine.
  */
void Engine::initialize(int argc, char *argv[]){
    debugMessage("engine initializing...");


    app_dir = QApplication::applicationDirPath();
    debugMessage("Application Dir: " + app_dir);

    if(QElapsedTimer::clockType() == QElapsedTimer::PerformanceCounter){
        debugMessage("PerformanceTimer in use");
    }

    //GLEW
    GLenum GlewInitResult;

    //init openGL 4.0
    /*
    glutInit(&argc, argv);
    glutInitContextVersion(4, 0);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_CONTINUE_EXECUTION
    );
    */
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwSetErrorCallback(error_callback);


    //creating the window
    window = new Window();
    //listener has to be set before initialization for debug output.
    windowTransmitter = window;
    windowTransmitter->addListener(debuggerListener);
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

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);



    debugMessage("Ideal thread number: " + QString::number(QThread::idealThreadCount()));
    idealThreadCount = QThread::idealThreadCount();

    //-1 == keep mainthread free
    threadAccountant = new ThreadAccountant(idealThreadCount);


    //init Streamer
    model_library = new ModelLibrary(threadAccountant);
    model_library->addListener(debuggerListener);
    model_library->initialize();


    //init Streamer
    light_library = new LightLibrary(threadAccountant);
    light_library->addListener(debuggerListener);
    light_library->initialize();


    //init keyboard
    k = new KeyBoard(window);
    k->addListener(debuggerListener);
    k->initialize();

    //init mouse
    m = new Mouse(window);
    m->addListener(debuggerListener);
    m->initialize();

    m->relativeCoordinates(true);

    /*
    x_angle = 0.0;
    y_angle = 0.0;
    */


    //init RENDERER
    r = new Renderer();
    r->addListener(debuggerListener);
    r->initialize();
    r->setPolygonMode(Renderer::PolygonModeStandard);


    cam = new Camera();

    r->setCamera(cam);
    r->setWindow(window);


    //register c function callbacks
    //glutDisplayFunc(&render_callback);
    //glutCloseFunc(&close_callback);
    //glutIdleFunc(&idle_callback);
    //glutTimerFunc(0, &timer_callback, 0);
    //glutKeyboardFunc(&keyboard_callback);

    //set default gl stuff
    glClearColor(0.5f,0.5f,0.5f,1.0f); //grey


    debugMessage("starting main event timer...");
    running = true;

    //here the "main 'thread' starts"
    t = new QTimer(this);
    QObject::connect(t,SIGNAL(timeout()),this,SLOT(eventLoop()));

    frameTime = 0;
    time = 0;
    //deltatime in ns (16 ms)
    deltaTime = 1000000000/60;
    accumulator = 0;
    timestep = 1.0f;

    elapseTimer.start();


    //1000 ms / 60 fps = 16.6 ms/second
    //16 makes some high cpu usage
    //17 is just fina actually but only 59 fps
    t->setInterval(16);
    t->start();



    fps_timer = new QTimer(this);
    QObject::connect(fps_timer,SIGNAL(timeout()),this,SLOT(timer()));
    fps_timer->setInterval(1000);
    fps_timer->start();

}

void Engine::setWindowTitle(QString title){
    if(running){
        window->setWindowTitle(title);
    }
}

void Engine::showDebugWindow(){
    if(!debug_visible){
        Event e;
        e.type = Event::EventDebuggerShow;
        this->transmit(e);
        debug_visible = true;
    }
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
    fps = frame_count;

    setWindowTitle("fps: " + QString::number(fps) +
                   "   @ " + QString::number(frameTime) + "ns/frame    timestep: " +
                   QString::number(timestep) + "   models: " +
                   QString::number(model_library->modelCount()));

    frame_count = 0;
}


void Engine::render()
{
    frame_count++;

    //timer timestep and so on...
    frameTime = elapseTimer.nsecsElapsed();
    elapseTimer.restart();
    //max frame time to avoid spiral of death
    //all values in nanosecs (1 ms = 1 000 000 ns)
    if(frameTime > 450000000){
        frameTime = 450000000;
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
        r->setModelLibrary(model_library);
        r->setLightLibrary(light_library);
        r->render();

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


//temprary...
Model * Engine::loadModel(QString path){
    return model_library->loadModel(path);
}

Light * Engine::loadLight(QString path){
    return light_library->loadLight(path);
}

void Engine::setCamera(Camera * cam){
    this->cam = cam;
    r->setCamera(this->cam);
}
