#include "renderer.h"

Renderer::Renderer(QObject *parent) :
    QThread(parent),
    render(false),
    abort(false)
{

}

Renderer::~Renderer(){
    //destructor: stop thread...
    mutex.lock();
    abort = true;
    mutex.unlock();
    wait();
}

void Renderer::start_render(){
    QMutexLocker locker(&mutex);

    render = true;
    abort = false;

    if (!isRunning()) {
        start(LowPriority);
        //start(HighPriority);
    }
    else{
        qDebug("RenderThread already running...");
    }
}

void Renderer::stop_render(){
    QMutexLocker locker(&mutex);
    render = false;
    abort = true;
}

void Renderer::run(){

    while(true){
        if (abort){
            qDebug("RenderThread aborting...");
            return;
        }

        mutex.lock();
        //copy thread sensitive data...
        mutex.unlock();



        //work here
    }


    //Thread needs to sleep too :D
    mutex.lock();
    if(!render){
        qDebug("EventThread stopped.");
        condition.wait(&mutex);
    }
    mutex.unlock();
}
