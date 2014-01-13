#ifndef WINDOW_H
#define WINDOW_H

#include <QString>
#include "Event/eventtransmitter.h"

#include "Graphics/OpenGL/OpenGL.h"

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

    bool isOpen();


private:
    //window settings
    QString window_title;
    int window_width;
    int window_height;
    int window_handle;

    bool created;

    void debugMessage(QString message);
};

#endif // WINDOW_H
