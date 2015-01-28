#include "mouse.h"

#include "Event/event.h"

//C
Mouse * ptr_global_mouse_instance = NULL;

void mousePressed_callback(GLFWwindow* win, int button, int action, int mods);
void mousescroll_callback(GLFWwindow* win,  double x, double y);
void mouseMoved_callback(GLFWwindow* win, double x, double y);



void mousePressed_callback(GLFWwindow* win, int button, int action, int mods){
    ptr_global_mouse_instance->mousePressed(button, action, mods);
}

void mousescroll_callback(GLFWwindow* win,  double x, double y){
    ptr_global_mouse_instance->mouseScrolled(x, y);
}

void mouseMoved_callback(GLFWwindow* win, double x, double y){
    ptr_global_mouse_instance->mouseMoved(x, y);
}

//C END

Mouse::Mouse(Window * win) :
    EventTransmitter()
{
    debugMessage("mouse created.");
    ptr_global_mouse_instance = this;
    mouseButtons = new bool[10];
    modifiers = 0;

    xpos = -1;
    ypos = -1;

    xscroll = 0;
    yscroll = 0;

    w = win;

    for(int i = 0; i < 10; i++){
        mouseButtons[i] = false;
    }
}

void Mouse::initialize(){
    debugMessage("mouse initializing...");

    glfwSetMouseButtonCallback(w->getGLFWwindow(),&mousePressed_callback);
    glfwSetCursorPosCallback(w->getGLFWwindow(),&mouseMoved_callback);
    glfwSetScrollCallback(w->getGLFWwindow(), &mousescroll_callback);

    debugMessage("mouse initialized.");
}



void Mouse::hideCursor(){
    //glutSetCursor(GLUT_CURSOR_NONE);
}

void Mouse::showCursor(){
    //glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
}

void Mouse::focusLostReset(){
    debugMessage("Resetting mouse");

    modifiers = 0;

    xpos = -1;
    ypos = -1;

    xscroll = 0;
    yscroll = 0;

    for(int i = 0; i < 10; i++){
        mouseButtons[i] = false;
    }
}

bool Mouse::isPressed(int button){
    return mouseButtons[button];
}

double Mouse::posX(){
    return xpos;
}

double Mouse::posY(){
    return ypos;
}

double  Mouse::scrollX(){
    double x = xscroll;
    xscroll = 0;
    return x;
}

double  Mouse::scrollY(){
    double y = yscroll;
    yscroll = 0;
    return y;
}

void Mouse::mousePressed (int button, int action, int mods) {
    debugMessage("mouseButton: " + QString::number(button));

    if(action == GLFW_PRESS){
        mouseButtons[button] = true;
    }
    else if(action == GLFW_RELEASE){
        mouseButtons[button] = false;
    }
    modifiers = mods;
}

void Mouse::mouseScrolled (double x, double y) {
    debugMessage("mouseScroll: " + QString::number(x) + "  " + QString::number(y));
    xscroll = x;
    yscroll = y;
}

void Mouse::mouseMoved (double x, double y) {
    debugMessage("mouseMove: " + QString::number(x) + "  "  + QString::number(y));
    xpos = x;
    ypos = y;
}

void Mouse::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    EventDebugger * ed = new EventDebugger(message);
    e.debugger = ed;
    this->transmit(e);
}
