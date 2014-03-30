#ifndef MOUSE_H
#define MOUSE_H

#include "Event/eventtransmitter.h"
#include "Graphics/OpenGL/OpenGL.h"

class Mouse : public EventTransmitter
{
public:
    Mouse();
    void initialize();

    bool isPressed(int button);
    bool isSpun(int wheel);
    int spinDirection();
    int posX();
    int posY();

    //callbacks
    void mousePressed (int button, int state, int x, int y);
    void wheelSpun(int wheel, int direction, int x, int y);
    void mouseMoved(int x, int y);

private:
    bool* mouseButtons;
    int wheelspin;
    int wheelspindir;

    int xpos;
    int ypos;

    void debugMessage(QString message);
};

#endif // MOUSE_H
