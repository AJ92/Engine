#ifndef MOUSE_H
#define MOUSE_H

#include "Event/eventtransmitter.h"
#include "Graphics/OpenGL/OpenGL.h"
#include "Graphics/Window/window.h"

class Window;
class Event;

class Mouse : public EventTransmitter
{
public:
    Mouse(Window * win);
    void initialize();

    bool isPressed(int button);
    double scrollX();
    double scrollY();
    double posX();
    double posY();

    void hideCursor();
    void showCursor();

    void focusLostReset();

    //callbacks
    void mousePressed (int button, int action, int mods);
    void mouseScrolled(double x, double y);
    void mouseMoved(double x, double y);

private:
    bool* mouseButtons;

    int modifiers;

    double xscroll;
    double yscroll;

    double xpos;
    double ypos;

    Window * w;

    void debugMessage(QString message);
};

#endif // MOUSE_H
