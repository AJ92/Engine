#include "keyboard.h"

//C
KeyBoard * ptr_global_keyboard_instance = NULL;

void keyPressed_callback(unsigned char key, int x, int y);
void keyUp_callback(unsigned char key, int x, int y);

void keySpecialPressed_callback(int key, int x, int y);
void keySpecialUp_callback(int key, int x, int y);


void keyPressed_callback(unsigned char key, int x, int y)
{
    ptr_global_keyboard_instance->keyPressed(key, x, y);
}

void keyUp_callback(unsigned char key, int x, int y){
    ptr_global_keyboard_instance->keyUp(key, x, y);
}


void keySpecialPressed_callback(int key, int x, int y)
{
    ptr_global_keyboard_instance->keySpecialPressed(key, x, y);
}

void keySpecialUp_callback(int key, int x, int y){
    ptr_global_keyboard_instance->keySpecialUp(key, x, y);
}
//C END

KeyBoard::KeyBoard() :
    EventTransmitter()
{
    debugMessage("keyboard created.");
    ptr_global_keyboard_instance = this;
    keyStates = new bool[256];
    keySpecialStates = new bool[256];
}

void KeyBoard::initialize(){
    debugMessage("keyboard initializing...");
    glutKeyboardFunc(keyPressed_callback); // Tell GLUT to use the method "keyPressed" for key presses
    glutKeyboardUpFunc(keyUp_callback); // Tell GLUT to use the method "keyUp" for key up events

    glutSpecialFunc(keySpecialPressed_callback); // Tell GLUT to use the method "keySpecial" for special key presses
    glutSpecialUpFunc(keySpecialUp_callback); // Tell GLUT to use the method "keySpecialUp" for special up key events
    debugMessage("keyboard initialized.");
}

bool KeyBoard::isPressed(unsigned char key){
    return keyStates[key];
}

bool KeyBoard::isSpecialPressed(unsigned char key){
    return keySpecialStates[key];
}

void KeyBoard::keyPressed (unsigned char key, int x, int y) {
    keyStates[key] = true; // Set the state of the current key to pressed
}

void KeyBoard::keyUp (unsigned char key, int x, int y) {
    keyStates[key] = false; // Set the state of the current key to not pressed
}

void KeyBoard::keySpecialPressed (int key, int x, int y) {
    keySpecialStates[key] = true; // Set the state of the current key to pressed
}

void KeyBoard::keySpecialUp (int key, int x, int y) {
    keySpecialStates[key] = false; // Set the state of the current key to not pressed
}

void KeyBoard::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    EventDebugger * ed = new EventDebugger(message);
    e.debugger = ed;
    this->transmit(e);
}
