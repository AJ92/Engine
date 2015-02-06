#include "window.h"

#include "Event/event.h"
//C

Window * ptr_global_window_instance = NULL;

void resize_callback(GLFWwindow* win, int width, int height);

void windowClose_callback(void);

void resize_callback(GLFWwindow* win, int width, int height)
{
    ptr_global_window_instance->resize(width, height);
}

void focus_callback(GLFWwindow* win, int focused)
{
    ptr_global_window_instance->focus(focused);
}


void windowClose_callback(void){
    ptr_global_window_instance->close();
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
    //window_handle = 0;
}

Window::~Window(){

}

void Window::initialize(){
    debugMessage("window initializing...");
    /*
    glutInitWindowSize(window_width, window_height);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
    window_handle = glutCreateWindow(window_title.toUtf8().constData());
    if(window_handle < 1) {
        debugMessage("ERROR (1): Window could not be created.");
        exit(EXIT_FAILURE);
    }

    //register c function callback
    glutReshapeFunc(&resize_callback);
    glutCloseFunc(&windowClose_callback);
    */


    //use 4.0 context

    //Anti Aliasing (useless... deferred renderer)
    //glfwWindowHint (GLFW_SAMPLES, 16);

    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    //use 3.3 context
    /*
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    */


    keyboard = 0;
    mouse = 0;

    window = glfwCreateWindow(window_width, window_height, window_title.toUtf8().constData(), NULL, NULL);
    glfwSetWindowSizeCallback(window,&resize_callback);
    glfwSetWindowFocusCallback(window,&focus_callback);
    glfwMakeContextCurrent (window);


    created = true;
    debugMessage("window initialized.");
}


void Window::setWindowTitle(QString title){
    window_title = title;
    if(created){
        glfwSetWindowTitle(window,window_title.toUtf8().constData());
    }
}

void Window::setWindowSize(int width, int height){
    if(created){
        glfwSetWindowSize(window,width, height);
    }
}

int Window::getWindowWidth(){
    return window_width;
}

int Window::getWindowHeight(){
    return window_height;
}

GLFWwindow* Window::getGLFWwindow(){
    return window;
}

//next 2 might need a rename to onResize an onClose.... so its clear it's an event or so...

void Window::resize(int width, int height){
    window_width = width;
    window_height = height;
    glViewport(0, 0, window_width, window_height);

    Event e;
    e.type = Event::EventWindowResize;
    e.window = new EventWindow(window_width, window_height);
    this->transmit(e);

    debugMessage("Window resize: " + QString::number(window_width) + "  " + QString::number(window_height));
}

void Window::close(){
    debugMessage("window closed.");
    created = false;
}

void Window::focus(int focused){
    debugMessage("Focus change:");
    if(focused == GL_FALSE){
        debugMessage("Focus lost");
        if(keyboard != 0){
            keyboard->focusLostReset();
        }
        if(mouse != 0){
            mouse->focusLostReset();
        }
    }
    else{
        debugMessage("Focus gained");
       //to be added
    }
}

bool Window::isOpen(){
    return created;
}

void Window::registerKeyboard(KeyBoard *k){
    keyboard = k;
}

void Window::registerMouse(Mouse *m){
    mouse = m;
}

void Window::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    EventDebugger * ed = new EventDebugger(message);
    e.debugger = ed;
    this->transmit(e);
}
