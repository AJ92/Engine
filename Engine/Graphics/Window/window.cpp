#include "window.h"


//C

Window * ptr_global_window_instance = NULL;

void resize_callback(int width, int height);

void resize_callback(int width, int height)
{
    ptr_global_window_instance->resize(width, height);
}

//C END





Window::Window() :
    EventTransmitter()
{
    debugMessage("window created.");
    created = false;

    ptr_global_window_instance = this;

    window_title = "Engine";
    window_width = 600;
    window_height = 400;
    window_handle = 0;
}

void Window::initialize(){
    debugMessage("window initializing...");
    glutInitWindowSize(window_width, window_height);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    window_handle = glutCreateWindow(window_title.toUtf8().constData());
    if(window_handle < 1) {
        debugMessage("ERROR (1): Window could not be created.");
        exit(EXIT_FAILURE);
    }

    //register c function callback
    glutReshapeFunc(&resize_callback);

    created = true;
    debugMessage("window initialized.");
}


void Window::setWindowTitle(QString title){
    window_title = title;
    if(created){
        glutSetWindowTitle(window_title.toUtf8().constData());
    }
}

void Window::setWindowSize(int width, int height){
    if(created){
        glutReshapeWindow(width, height);
    }
}

int Window::getWindowWidth(){
    return window_width;
}

int Window::getWindowHeight(){
    return window_height;
}

void Window::resize(int width, int height){
    window_width = width;
    window_height = height;
    glViewport(0, 0, window_width, window_height);
    debugMessage("Window resize: " + QString::number(window_width) + "  " + QString::number(window_height));
}

void Window::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    EventDebugger * ed = new EventDebugger(message);
    e.debugger = ed;
    this->transmit(e);
}
