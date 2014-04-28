#ifndef MOUSE_H
#define MOUSE_H

#include "Event/eventtransmitter.h"
#include "Graphics/OpenGL/OpenGL.h"
#include "Graphics/Window/window.h"


class Mouse : public EventTransmitter
{
public:
    Mouse(Window * win);
    void initialize();

    bool isPressed(int button);
    bool isSpun(int wheel);
    int spinDirection();
    int posX();
    int posY();

    void relativeCoordinates(bool move);
    void setTrapBorder(int value);
    void trapMouse(bool trap);
    void hideCursor();
    void showCursor();

    //callbacks
    void mousePressed (int button, int action, int mods);
    void wheelSpun(int wheel, int direction, int x, int y);
    void mouseMoved(double x, double y);

private:
    bool* mouseButtons;

    int modifiers;

    int wheelspin;
    int wheelspindir;

    double xpos;
    double ypos;

    //movement == true; posX and posY will give you relative coordinates
    //movement == false; posX and posY will give you global coordinates
    bool movement;
    bool warped;
    int trapBorder;
    bool trapMouseInFrame;

    int old_x_pos;
    int old_y_pos;

    Window * w;

    void debugMessage(QString message);
};

#endif // MOUSE_H
