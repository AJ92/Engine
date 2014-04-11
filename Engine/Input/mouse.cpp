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

Mouse::Mouse(Window * win) :
    EventTransmitter()
{
    debugMessage("keyboard created.");
    ptr_global_mouse_instance = this;
    mouseButtons = new bool[10];

    xpos = -1;
    ypos = -1;
    wheelspin = -1;
    wheelspindir = -1;

    w = win;

    movement = false;
    warped = false;

    old_x_pos = 0;
    old_y_pos = 0;

    for(int i = 0; i < 10; i++){
        mouseButtons[i] = false;
    }
}

void Mouse::initialize(){
    debugMessage("mouse initializing...");
    glutMouseFunc(mousePressed_callback);
    glutMouseWheelFunc(wheelSpun_callback);
    glutPassiveMotionFunc(mouseMoved_callback);
    glutMotionFunc(mouseMoved_callback);
    debugMessage("mouse initialized.");
}

void Mouse::relativeCoordinates(bool move){
    this->movement = move;
}

void Mouse::hideCursor(){
    glutSetCursor(GLUT_CURSOR_NONE);
}

void Mouse::showCursor(){
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
}

bool Mouse::isPressed(int button){
    return mouseButtons[button];
}

int Mouse::posX(){
    if(movement){
        int moved_x = old_x_pos - xpos;
        old_x_pos = xpos;
        return moved_x;
    }
    else{
        return xpos;
    }
}

int Mouse::posY(){
    if(movement){
        int moved_y = old_y_pos - ypos;
        old_y_pos = ypos;
        return moved_y;
    }
    else{
        return ypos;
    }
}

bool Mouse::isSpun(int wheel){
    if(wheelspin == wheel){
        wheelspin = -1;
        return true;
    }
    return false;
}

int Mouse::spinDirection(){
    return wheelspindir;
}

void Mouse::mousePressed (int button, int state, int x, int y) {
    //debugMessage("mouseButton: " + QString::number(button));
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
    //debugMessage("mouseWheel: " + QString::number(wheel) + "  " + QString::number(direction));
    wheelspin = wheel;
    wheelspindir = direction;
    xpos = x;
    ypos = y;
}

void Mouse::mouseMoved (int x, int y) {
    //debugMessage("mouseMove: " + QString::number(x) + "  "  + QString::number(y));
    xpos = x;
    ypos = y;
    if(movement && !warped){
        if(xpos < 30 || ypos < 30 || xpos > (w->getWindowWidth() - 30) || ypos > (w->getWindowHeight() - 30)){
            glutWarpPointer(w->getWindowWidth()/2,w->getWindowHeight()/2);
            xpos = w->getWindowWidth()/2;
            ypos = w->getWindowHeight()/2;
            old_x_pos = xpos;
            old_y_pos = ypos;
            warped = true;
            return;
        }
    }
    warped = false;
}

void Mouse::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    EventDebugger * ed = new EventDebugger(message);
    e.debugger = ed;
    this->transmit(e);
}
