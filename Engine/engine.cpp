#include "engine.h"


#include "Debug/Ui/debugwindow.h"
#include "Graphics/freeglut/include/GL/freeglut.h"

#include "Event/eventtransmitter.h"

/*!
  Main class.
  Manages all the crazy stuff an engine needs to manage.

  This is actually a wrapper for all the other stuff like
  window management... renderer... physics and god knows what else...
  */


// C part
Engine * ptr_global_instance = NULL;
void display_callback(void);
void keyboard_callback(unsigned char key, int x, int y);

void display_callback(){
    ptr_global_instance->display();
}

void keyboard_callback(unsigned char key, int x, int y){
    ptr_global_instance->keyboard(key, x, y);
}
// C part END


Engine::Engine()
{

}

/*!
  If everything is set up, this command starts the engine.
  */
void Engine::initialize(int argc, char *argv[]){



    //TEST
    EventTransmitter et;

    EventListener el;

    et.addListener(el);

    et.transmit(Event());

    et.removeListener(el);




    DebugWindow w;

    w.show();

    w.add_log("Engine started.");


    glutInit(&argc, argv);

    glutCreateWindow("GLUT Test");



    //old c
    //glutKeyboardFunc(&keyboard);
    //glutDisplayFunc(&display);

    //register c function callbacks

    ptr_global_instance = this;
    glutDisplayFunc(&display_callback);
    glutKeyboardFunc(&keyboard_callback);

    glutMainLoop();

}


void Engine::keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '\x1B':
        exit(EXIT_SUCCESS);
        break;
    }
}


void Engine::display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f( 0.5f, -0.5f);
    glVertex2f( 0.5f,  0.5f);
    glVertex2f(-0.5f,  0.5f);
    glEnd();

    glFlush();
}
