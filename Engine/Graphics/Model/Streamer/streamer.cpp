#include "streamer.h"

Streamer::Streamer(ThreadAccountant * ta, QObject *parent) :
    EventListener(),
    EventTransmitter(),
    QObject(parent),
    ta(ta)
{

}


void Streamer::initialize(){
    debugMessage("streamer initializing...");

    t = new QTimer(this);
    QObject::connect(t,SIGNAL(timeout()),this,SLOT(assignModeltoThread()));
    //every 200 ms
    t->setInterval(200);
    t->start();

    debugMessage("streamer initialized.");
}


void Streamer::streamModelToDisk(Model * m){
    //might stay unused
}

void Streamer::streamModelFromDisk(Model * m){

    //if there is room far another thread create one!
    if(ta->addThread()){
        //store model pointer and id
        id_model_map[m->id()] = m;


        QThread* thread = new QThread();
        StreamToDisk* worker = new StreamToDisk(m);
        worker->moveToThread(thread);
        connect(worker, SIGNAL(error(QString)), this, SLOT(debugMessage(QString)));
        connect(thread, SIGNAL(started()), worker, SLOT(stream()));
        connect(worker, SIGNAL(finished(Model*,unsigned long long)), thread, SLOT(quit()));

        //here we need a slot for returning the model or so...
        connect(worker, SIGNAL(finished(Model*, unsigned long long)), this, SLOT(streamModelFromDiskFinished(Model*, unsigned long long)));

        connect(worker, SIGNAL(finished(Model*,unsigned long long)), worker, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        thread->start();
    }
    //ok there is none so queue the model :D
    else{
        model_queue.push(m);
    }
}


//slots

void Streamer::assignModeltoThread(){
    //remove model from queue if there is any
    //and try to assign it to a thread
    //if all threads are in use the model will go back into the list...
    if(model_queue.size() > 0){
        Model * m = model_queue.front();
        model_queue.pop();
        streamModelFromDisk(m);
    }
}

void Streamer::streamModelToDiskFinished(Model * m, unsigned long long id){
    //now set the pointer right...
}

void Streamer::streamModelFromDiskFinished(Model * m, unsigned long long id){
    //now set the pointer right...

    Model * mdl = id_model_map[id];
    *mdl = *m;


    id_model_map.erase(id);
    ta->removeThread();

    //we are now in mainthread and can load GL data
    mdl->loadGLdata();

}


//EVENT TRANSMITTER  now AS SLOT
void Streamer::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}
