#include "streamthread.h"

StreamThread::StreamThread(QObject *parent) :
    EventTransmitter(),
    QThread(parent),
    running(false),
    abort(false)
{

}

void StreamThread::init(){

}

StreamThread::~StreamThread(){
    //destructor: stop thread...
    mutex.lock();
    abort = true;
    running = false;
    mutex.unlock();
    wait();
}


void StreamThread::start_streamThread(){
    QMutexLocker locker(&mutex);

    running = true;
    abort = false;

    if (!isRunning()) {
        start(LowPriority);
        //start(HighPriority);
    }
    else{
        qDebug("StreamThread already running...");
    }
}

void StreamThread::stop_streamThread(){
    QMutexLocker locker(&mutex);
    running = false;
    abort = true;
}

void StreamThread::run(){

    while(true){
        if (abort){
            qDebug("StreamThread aborting...");
            return;
        }

        mutex.lock();
        //copy thread sensitive data...
        mutex.unlock();


        glutMainLoopEvent();

        usleep(5000);

        //work here
    }


    //Thread needs to sleep too :D
    mutex.lock();
    if(!running){
        qDebug("StreamThread stopped.");
        condition.wait(&mutex);
    }
    mutex.unlock();
}

void StreamThread::debugMessage(QString message){
    Event e(Event::EventDebuggerMessage);
    e.setString(message);
    this->transmit(e);
}
