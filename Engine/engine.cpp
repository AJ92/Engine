#include "engine.h"





/*!
  Main class.
  Manages all the crazy stuff an engine needs to manage.

  This is actually a wrapper for all the other stuff like
  window management... renderer... physics and god knows what else...
  */


// C part
Engine * ptr_global_engine_instance = NULL;

void render_callback(void);
void idle_callback(void);
void timer_callback(int value);
void keyboard_callback(unsigned char key, int x, int y);


void render_callback(){
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
Engine::Engine() :
    EventTransmitter()
{
    ptr_global_engine_instance = this;
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

/*!
  If everything is set up, this command starts the engine.
  */
void Engine::initialize(int argc, char *argv[]){
    debugMessage("engine initializing...");

    //threads should start here...

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

    //register c function callbacks
    glutDisplayFunc(&render_callback);
    glutIdleFunc(&idle_callback);
    glutTimerFunc(0, &timer_callback, 0);
    glutKeyboardFunc(&keyboard_callback);

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

    running = true;
    debugMessage("engine initialized. starting main loop.");

    //here the "main thread starts"
    glutMainLoop();
    running = false;

    //The window was closed...
    debugMessage("window closed. mainloop terminated.");

    //temporary clean up... should go into destructor...
    this->removeListener(debuggerListener);
}


void Engine::keyboard(unsigned char key, int x, int y)
{
    debugMessage("Keypress: " + QString(key));
    switch (key)
    {
    case '\x1B':
        exit(EXIT_SUCCESS);
        break;
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
    /* OLD STUFF
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f( 0.5f, -0.5f);
    glVertex2f( 0.5f,  0.5f);
    glVertex2f(-0.5f,  0.5f);
    glEnd();

    glFlush();
    */

    frame_count++;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutSwapBuffers();
    glutPostRedisplay();

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
