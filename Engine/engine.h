#ifndef ENGINE_H
#define ENGINE_H

#include <QString>
#include <QTime>

#include "Debug/Ui/debugwindow.h"

#include "Graphics/glew/include/GL/glew.h"
#include "Graphics/freeglut/include/GL/freeglut.h"

#include "Event/eventtransmitter.h"


class Engine
{
public:
    Engine();
    void initialize(int argc, char *argv[]);

    void keyboard(unsigned char key, int x, int y);
    void resize(int width, int height);
    void idle();
    void timer(int value);
    void render();


    void setWindowTitle(QString title);
    void showDebugWindow();
    void hideDebugWindow();

private:

    bool running;

    //window settings
    QString window_title;
    int window_width;
    int window_height;
    int window_handle;


    //Debug settings
    DebugWindow w;
    bool debug_visible;

    //FPS settings
    int frame_count;
    int fps;
};

#endif // ENGINE_H
