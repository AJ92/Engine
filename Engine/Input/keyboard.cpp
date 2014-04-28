#include "keyboard.h"

//C
KeyBoard * ptr_global_keyboard_instance = NULL;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    ptr_global_keyboard_instance->key(key, scancode, action, mods);
}

//C END

KeyBoard::KeyBoard(Window* window) :
    EventTransmitter()
{
    debugMessage("keyboard created.");
    ptr_global_keyboard_instance = this;
    win = window;
    keyStates = new bool[256];
    keyModifiers = new int[256];
    modifier = 0;

    for(int i = 0; i < 256; i++){
        keyStates[i] = false;
        keyModifiers[i] = 0;
    }
}

void KeyBoard::initialize(){
    debugMessage("keyboard initializing...");
    glfwSetKeyCallback(win->getGLFWwindow(), &key_callback);
    debugMessage("keyboard initialized.");
}

void KeyBoard::key(int key, int scancode, int action, int mods){
    debugMessage("key: " + QString::number(scancode));
    if(action == GLFW_PRESS || action == GLFW_REPEAT){
        keyStates[scancode] = true;
    }
    else{
        keyStates[scancode] = false;
    }
    keyModifiers[scancode] = mods;
}

bool KeyBoard::isPressed(int key){
    return keyStates[key];
}

void KeyBoard::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    EventDebugger * ed = new EventDebugger(message);
    e.debugger = ed;
    this->transmit(e);
}
