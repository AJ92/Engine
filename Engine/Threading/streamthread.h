#ifndef STREAMTHREAD_H
#define STREAMTHREAD_H

#include <QThread>
#include <QWaitCondition>
#include <QMutexLocker>
#include <QMutex>
#include <QString>

#include "Graphics/OpenGL/OpenGL.h"

#include "Event/eventtransmitter.h"

class StreamThread : public QThread , virtual public EventTransmitter
{
    Q_OBJECT
public:
    StreamThread();
    ~StreamThread();

    void init();

    void start();
    void stop();

protected:
    void run();

private:
    QMutex mutex;
    QWaitCondition condition;
    bool running;
    bool abort;

    void debugMessage(QString message);
};

#endif // STREAMTHREAD_H
