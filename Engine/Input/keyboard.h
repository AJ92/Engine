#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Event/eventtransmitter.h"
#include "Graphics/OpenGL/OpenGL.h"
#include "Graphics/Window/window.h"

class KeyBoard : public EventTransmitter
{
public:
    KeyBoard(Window* window);
    void initialize();

    void key(int key, int scancode, int action, int mods);
    bool isPressed(int key);

private:
    //ASCII KEYS
    bool* keyStates;
    int* keyModifiers;
    int modifier;

    Window* win;

    void debugMessage(QString message);
};

#endif // KEYBOARD_H
