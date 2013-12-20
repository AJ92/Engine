#ifndef STREAMTHREAD_H
#define STREAMTHREAD_H

#include <QThread>
#include <QWaitCondition>
#include <QMutexLocker>
#include <QMutex>
#include <QString>

#include "Graphics/freeglut/include/GL/freeglut.h"
#include "Event/eventtransmitter.h"

class StreamThread : public QThread , virtual public EventTransmitter
{
    Q_OBJECT
public:
    StreamThread(QObject *parent = 0);
    ~StreamThread();

    void init();

    void start_streamThread();
    void stop_streamThread();

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
