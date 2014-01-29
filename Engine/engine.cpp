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
void idle_callback(void);
void timer_callback(int value);
void keyboard_callback(unsigned char key, int x, int y);


void render_callback(void){
    ptr_global_engine_instance->render();
}

void idle_callback(void)
{
    ptr_global_engine_instance->idle();
}


void timer_callback(int value){
    ptr_global_engine_instance->timer(value);
}

void keyboard_callback(unsigned char key, int x, int y){
    ptr_global_engine_instance->keyboard(key, x, y);
}
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

    idealThreadCount = 1;

    //init debugger and it's listener

    debugger = new Debugger();
    debuggerListener = debugger;
    addListener(debuggerListener);

    debugMessage("engine created.");
}

Engine::~Engine(){
    running = false;
    qDebug("engine stopped.");
}

/*!
  If everything is set up, this command starts the engine.
  */
void Engine::initialize(int argc, char *argv[]){
    debugMessage("engine initializing...");


    //GLEW
    GLenum GlewInitResult;

    //init openGL 4.0
    glutInit(&argc, argv);
    glutInitContextVersion(4, 0);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_CONTINUE_EXECUTION
    );

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


    //init Streamer
    model_library = new ModelLibrary(idealThreadCount,100);
    model_library->addListener(debuggerListener);
    model_library->initialize();



    //init RENDERER
    r = new Renderer();
    r->addListener(debuggerListener);
    r->initialize();
    r->setPolygonMode(Renderer::PolygonModeFill);


    //register c function callbacks
    glutDisplayFunc(&render_callback);
    //glutCloseFunc(&close_callback);
    glutIdleFunc(&idle_callback);
    glutTimerFunc(0, &timer_callback, 0);
    glutKeyboardFunc(&keyboard_callback);


    debugMessage("starting main event timer...");
    running = true;

    //here the "main 'thread' starts"
    t = new QTimer(this);
    QObject::connect(t,SIGNAL(timeout()),this,SLOT(eventLoop()));


    //1000 ms / 60 fps = 16.6 ms/second
    t->setInterval(16);
    t->start();
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

bool Engine::isRunning(){
    return running;
}

int Engine::getFps(){
    return fps;
}

void Engine::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}



//CALLBACKS
void Engine::keyboard(unsigned char key, int x, int y)
{
    debugMessage("Keypress: " + QString(key));
    switch (key)
    {
    case '\x1B':
        exit(EXIT_SUCCESS);
        break;
    case '1':
        {
            Event e1;
            e1.type = Event::EventDebuggerShow;
            this->transmit(e1);
        }
        break;
    case '2':
        {
            Event e2;
            e2.type = Event::EventDebuggerHide;
            this->transmit(e2);
        }
        break;
    case 'l':
        {
            Model * m2 = loadModel("C://Users//AJ//Desktop//Code//QTProjects//Engine//Engine//misc//models//kv3.obj");
            debugMessage(QString::number(m2->id()));
        }
    }
}

void Engine::idle(){
    glutPostRedisplay();
}

void Engine::timer(int value){
    if (0 != value) {
        fps = frame_count * 4;
    }
    frame_count = 0;
    glutTimerFunc(250, &timer_callback, 1);
}


void Engine::render()
{
    frame_count++;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    r->render();

    glutSwapBuffers();
    glutPostRedisplay();
}


//SLOTS
void Engine::eventLoop(){
    glutMainLoopEvent();
    setWindowTitle(QString::number(getFps()));
}


//temprary...
Model * Engine::loadModel(QString path){
    return model_library->loadModel(path);
}

void Engine::transferModelsToMainThread(){

}
