#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QThread>
#include <QWaitCondition>
#include <QMutexLocker>
#include <QMutex>
#include <QString>

#include "Graphics/freeglut/include/GL/freeglut.h"
#include "Event/eventtransmitter.h"

class MainThread : public QThread , virtual public EventTransmitter
{
    Q_OBJECT
public:
    MainThread(QObject *parent = 0);
    ~MainThread();

    void start_mainThread();
    void stop_mainThread();


    //callbacks
    void keyboard(unsigned char key, int x, int y);
    void idle();
    void timer(int value);
    void render();


protected:
    void run();

private:
    QMutex mutex;
    QWaitCondition condition;
    bool running;
    bool abort;



    //FPS settings
    int frame_count;
    int fps;

    void debugMessage(QString message);
};

#endif // MAINTHREAD_H
