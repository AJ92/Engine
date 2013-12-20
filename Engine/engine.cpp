#include "engine.h"





/*!
  Main class.
  Manages all the crazy stuff an engine needs to manage.

  This is actually a wrapper for all the other stuff like
  window management... renderer... physics and god knows what else...
  */





/*!
  Sets on object creation the pointer for the C callback wrapper.
  */
Engine::Engine() :
    EventTransmitter()
{
    running = false;

    debug_visible = false;
    frame_count = 0;
    fps = 0;

    //init debugger and it's listener
    debugger = new Debugger();
    debuggerListener = debugger;
    addListener(debuggerListener);

    debugMessage("engine created.");

}

Engine::~Engine(){
    mainThread->stop_mainThread();
    streamThread->stop_streamThread();
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
        GLUT_ACTION_GLUTMAINLOOP_RETURNS
    );

    //creating the window
    window = new Window();
    //listener has to be set before initialization for debug output.
    windowTransmitter = window;
    windowTransmitter->addListener(debuggerListener);
    //CONNECT RESIZE EVENT HERE
    window->initialize();


    //GLEW
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

    debugMessage("engine initialized. starting main loop.");

    //start main thread
    mainThread = new MainThread();
    mainThreadTransmitter = mainThread;
    mainThreadTransmitter->addListener(debuggerListener);
    mainThread->init();
    mainThread->start_mainThread();

    //start stream thread
    streamThread = new StreamThread();
    streamThreadTransmitter = streamThread;
    streamThreadTransmitter->addListener(debuggerListener);
    streamThread->init();
    streamThread->start_streamThread();


    //here the "main thread starts"
    //glutMainLoop();

    debugMessage("main loop started as thread. running.");
    running = true;

}

void Engine::setWindowTitle(QString title){
    if(running){
        window->setWindowTitle(title);
    }
}

void Engine::showDebugWindow(){
    if(!debug_visible){
        Event e(Event::EventDebuggerShow);
        this->transmit(e);
        debug_visible = true;
    }
}

void Engine::hideDebugWindow(){
    if(debug_visible){
        Event e(Event::EventDebuggerHide);
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
    return window->getWindowWidth();
}

int Engine::getWindowHeight(){
    return window->getWindowHeight();
}

int Engine::getFps(){
    return fps;
}

void Engine::debugMessage(QString message){
    Event e(Event::EventDebuggerMessage);
    e.setString(message);
    this->transmit(e);
}
