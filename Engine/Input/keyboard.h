#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Event/eventtransmitter.h"
#include "Graphics/OpenGL/OpenGL.h"

class KeyBoard : public EventTransmitter
{
public:
    KeyBoard();
    void initialize();

    bool isPressed(unsigned char key);
    bool isSpecialPressed(unsigned char key);

    void keyPressed (unsigned char key, int x, int y);
    void keyUp (unsigned char key, int x, int y);

    void keySpecialPressed (int key, int x, int y);
    void keySpecialUp (int key, int x, int y);

private:
    //ASCII KEYS
    bool* keyStates;

    //SPECIAL KEYS (e.g. arrow up/down...)
    bool* keySpecialStates;

    void debugMessage(QString message);
};

#endif // KEYBOARD_H
