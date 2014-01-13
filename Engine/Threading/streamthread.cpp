#include "streamthread.h"

StreamThread::StreamThread() :
    EventTransmitter(),
    QThread(),
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
        debugMessage("Starting StreamThread...");
        start(LowPriority);
        //start(HighPriority);
    }
    else{
        debugMessage("StreamThread already running...");
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
            //debugMessage("StreamThread aborting...");
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
        //debugMessage("StreamThread stopped.");
        qDebug("StreamThread stopped.");
        condition.wait(&mutex);
    }
    mutex.unlock();
}

void StreamThread::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    EventDebugger * ed = new EventDebugger(message);
    e.debugger = ed;
    this->transmit(e);
}
