#ifndef WINDOW_H
#define WINDOW_H

#include <QString>
#include "Event/eventtransmitter.h"

#include "Graphics/OpenGL/OpenGL.h"
#include "Input/keyboard.h"
#include "Input/mouse.h"

class KeyBoard;
class Mouse;
class Event;

class Window : public EventTransmitter
{
public:
    Window();

    void initialize();

    void setWindowTitle(QString title);
    void setWindowSize(int width, int height);
    int getWindowWidth();
    int getWindowHeight();

    void resize(int width, int height);
    void close();
    void focus(int focused);

    bool isOpen();

    void registerKeyboard(KeyBoard *k);
    void registerMouse(Mouse *m);

    GLFWwindow* getGLFWwindow();


private:
    //window settings
    GLFWwindow* window;

    //used for focus callback...
    KeyBoard *keyboard;
    Mouse *mouse;

    QString window_title;
    int window_width;
    int window_height;

    //int window_handle;

    bool created;

    void debugMessage(QString message);
};

#endif // WINDOW_H
