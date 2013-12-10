#include "engine.h"





/*!
  Main class.
  Manages all the crazy stuff an engine needs to manage.

  This is actually a wrapper for all the other stuff like
  window management... renderer... physics and god knows what else...
  */


// C part
Engine * ptr_global_engine_instance = NULL;

void resize_callback(int width, int height);
void render_callback(void);
void idle_callback(void);
void timer_callback(int value);
void keyboard_callback(unsigned char key, int x, int y);

void resize_callback(int width, int height)
{
    ptr_global_engine_instance->resize(width, height);
}

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
Engine::Engine()
{
    ptr_global_engine_instance = this;

    running = false;

    window_title = "Engine";

    window_width = 600;
    window_height = 400;

    window_handle = 0;

    debug_visible = false;
    frame_count = 0;
    fps = 0;
}

/*!
  If everything is set up, this command starts the engine.
  */
void Engine::initialize(int argc, char *argv[]){

    w.add_log("Engine started.");


    //threads should start here...



    //main thread starts here (render and keyboard)...

    //GLEW
    GLenum GlewInitResult;


    //freeGLUT
    glutInit(&argc, argv);


    glutInitContextVersion(4, 0);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS
    );

    glutInitWindowSize(window_width, window_height);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);


    window_handle = glutCreateWindow(window_title.toUtf8().constData());

    if(window_handle < 1) {
        w.add_log("ERROR (1): Window could not be created.");
        exit(EXIT_FAILURE);
    }


    //old c
    //glutKeyboardFunc(&keyboard);
    //glutDisplayFunc(&display);

    //register c function callbacks

    glutReshapeFunc(&resize_callback);
    glutDisplayFunc(&render_callback);
    glutIdleFunc(&idle_callback);
    glutTimerFunc(0, &timer_callback, 0);

    glutKeyboardFunc(&keyboard_callback);
    //freeGLUT END



    //GLEW
    GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult) {
        w.add_log("ERROR (2): " + QString((char*)glewGetErrorString(GlewInitResult)));
        exit(EXIT_FAILURE);
    }

    w.add_log("INFO: OpenGL Version: " + QString((char*)glGetString(GL_VERSION)));
    w.add_log("INFO: OpenGL Vendor: " + QString((char*)glGetString(GL_VENDOR)));
    w.add_log("INFO: OpenGL Renderer: " + QString((char*)glGetString(GL_RENDERER)));
    w.add_log("INFO: OpenGL Shading Language version: " + QString((char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));

    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);


    running = true;

    glutMainLoop();


    w.add_log("Window closed.");
}


void Engine::keyboard(unsigned char key, int x, int y)
{
    w.add_log("Keypress: " + QString(key));
    switch (key)
    {
    case '\x1B':
        exit(EXIT_SUCCESS);
        break;
    }
}

void Engine::resize(int width, int height){
    window_width = width;
    window_height = height;
    glViewport(0, 0, window_width, window_height);
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
    window_title = title;
    if(running){
        glutSetWindowTitle(window_title.toUtf8().constData());
    }
}

void Engine::showDebugWindow(){
    if(!debug_visible){
        w.show();
        debug_visible = true;
    }
}

void Engine::hideDebugWindow(){
    if(debug_visible){
        w.hide();
        debug_visible = false;
    }
}
