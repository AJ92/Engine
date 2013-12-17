#ifndef RENDERER_H
#define RENDERER_H


#include <QThread>
#include <QWaitCondition>
#include <QMutexLocker>
#include <QMutex>
#include <QString>

#include "Graphics/glew/include/GL/glew.h"
#include "Graphics/freeglut/include/GL/freeglut.h"

class Renderer : public QThread
{
    Q_OBJECT
public:
    Renderer(QObject *parent = 0);
    ~Renderer();

    void start_render();
    void stop_render();

protected:
    void run();

private:
    QMutex mutex;
    QWaitCondition condition;


    bool render;
    bool abort;
};

#endif // RENDERER_H
