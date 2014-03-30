#include "mouse.h"

//C
Mouse * ptr_global_mouse_instance = NULL;

void mousePressed_callback(int button, int state, int x, int y);
void wheelSpun_callback(int wheel, int direction, int x, int y);
void mouseMoved_callback(int x, int y);



void mousePressed_callback(int button, int state, int x, int y){
    ptr_global_mouse_instance->mousePressed(button, state, x, y);
}

void wheelSpun_callback(int wheel, int direction, int x, int y){
    ptr_global_mouse_instance->wheelSpun(wheel, direction, x, y);
}

void mouseMoved_callback(int x, int y){
    ptr_global_mouse_instance->mouseMoved(x, y);
}

//C END

Mouse::Mouse() :
    EventTransmitter()
{
    debugMessage("keyboard created.");
    ptr_global_mouse_instance = this;
    mouseButtons = new bool[10];

    xpos = -1;
    ypos = -1;
    wheelspin = -1;
    wheelspindir = -1;

    for(int i = 0; i < 10; i++){
        mouseButtons[i] = false;
    }
}

void Mouse::initialize(){
    debugMessage("mouse initializing...");
    glutMouseFunc(mousePressed_callback);
    glutMouseWheelFunc(wheelSpun_callback);
    glutPassiveMotionFunc(mouseMoved_callback);
    debugMessage("mouse initialized.");
}

bool Mouse::isPressed(int button){
    return mouseButtons[button];
}

int Mouse::posX(){
    return xpos;
}

int Mouse::posY(){
    return ypos;
}

bool Mouse::isSpun(int wheel){
    if(wheelspin == wheel){
        wheelspin = -1;
        return true;
    }
}

int Mouse::spinDirection(){
    return wheelspindir;
}

void Mouse::mousePressed (int button, int state, int x, int y) {
    debugMessage("mouseButton: " + QString::number(button));
    if(state == GLUT_UP){
        mouseButtons[button] = true;
    }
    else if(state == GLUT_DOWN){
        mouseButtons[button] = false;
    }
    xpos = x;
    ypos = y;
}

void Mouse::wheelSpun (int wheel, int direction, int x, int y) {
    debugMessage("mouseWheel: " + QString::number(wheel) + "  " + QString::number(direction));
    wheelspin = wheel;
    wheelspindir = direction;
    xpos = x;
    ypos = y;
}

void Mouse::mouseMoved (int x, int y) {
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
