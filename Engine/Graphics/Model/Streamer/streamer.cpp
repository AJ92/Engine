#include "streamer.h"

Streamer::Streamer(int maxThreads, QObject *parent) :
    EventListener(),
    EventTransmitter(),
    QObject(parent),
    maxThreads(maxThreads)
{
    //need to intialize all threads and just dispatch the model loads or unloads...
}


void Streamer::initialize(){
    debugMessage("streamer initializing...");
    debugMessage("streamer initialized.");
}


void Streamer::streamModelToDisk(Model * m){
    //might stay unused
}

void Streamer::streamModelFromDisk(Model * m){
    //this one is far more usefull atm...

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


//signals

void Streamer::streamModelToDiskFinished(Model * m, unsigned long long id){
    //now set the pointer right...
}

void Streamer::streamModelFromDiskFinished(Model * m, unsigned long long id){
    //now set the pointer right...

    Model * mdl = id_model_map[id];
    mdl = m;

    id_model_map.erase(id);

}


//EVENT TRANSMITTER  now AS SLOT
void Streamer::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}
