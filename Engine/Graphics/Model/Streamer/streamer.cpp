#include "streamer.h"
#include <QApplication>

#include "Event/event.h"
#include "Graphics/Model/model.h"

Streamer::Streamer(ThreadAccountant * ta, QObject *parent) :
    EventListener(),
    EventTransmitter(),
    QObject(parent),
    models_per_thread(1),
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
    //put the model into the queue
    model_list.append(m);
    t->start();
}

void Streamer::setModelsPerThread(int model_count){
    if(model_count>0){
        models_per_thread = model_count;
    }
}


//slots

void Streamer::assignModeltoThread(){
    //remove model from list if there is any
    //and try to assign it to a thread
    //if all threads are in use the model will go back into the list...

    //qDebug("model_list: %i     finished_model_list: %i", model_list.size(), finished_model_list.size());

    bool keep_timer = false;

    //process models that wait for loading (DISK IOs)
    if(model_list.size() > 0){
        //we have models in the list
        //assign models_per_thread models per thread if possible
        if(model_list.size() < models_per_thread){
            models_per_thread = model_list.size();
        }

        if(ta->addThread()){
            while(model_list.size() >= models_per_thread){
                QList<Model*> model_list_for_thread;
                for(int i = 0; i < models_per_thread; i++){
                    Model *m = model_list.first();
                    id_model_map[m->id()] = m; //map id and model
                    model_list_for_thread.append(m);
                    model_list.pop_front();
                }
                //list filled - start thread with queue
                assignModelListToThread(model_list_for_thread);
            }
        }
        keep_timer = true;
    }

    //process models that wait for gpu (GPU IOs)
    if(finished_model_list.size() > 0){
        for(int i = 0; i < finished_model_list.size(); i++){
            Model * m = finished_model_list.front();

            //we are now in mainthread and can load GL data
            m->loadGLdata();
            finished_model_list.pop_front();
            //the model is now done and we send an event to the modellib
            Event e;
            e.type = Event::EventModelStreamedFromDisk;
            e.streamer = new EventStreamer(m);
            this->transmit(e);
        }
        keep_timer = true;
    }
    if(!keep_timer){
        //t->stop();
    }
}

void Streamer::assignModelListToThread(QList<Model *> model_list){
    qDebug() << "Creating new thread...";
    QThread* thread = new QThread();

    qDebug() << "   QApplication's Thread (aka Mainthread): " << QApplication::instance()->thread();
    qDebug() << "   Current thread: " << QThread::currentThread();
    qDebug() << "   Thread to move: " << thread;

    StreamToDisk* worker = new StreamToDisk(model_list);

    qDebug() << "   Worker thread: " << worker->thread();

    worker->moveToThread(thread);
    QObject::connect(worker, SIGNAL(error(QString)), this, SLOT(debugMessage(QString)), Qt::QueuedConnection);
    QObject::connect(thread, SIGNAL(started()), worker, SLOT(stream()), Qt::QueuedConnection);
    //here we need a slot for returning the model or so...
    QObject::connect(worker, SIGNAL(loaded(Model*, unsigned long long)),
            this, SLOT(streamModelFromDiskFinished(Model*, unsigned long long)), Qt::QueuedConnection);
    QObject::connect(worker, SIGNAL(finished()),this, SLOT(streamThreadFinished()), Qt::QueuedConnection);
    QObject::connect(worker, SIGNAL(finished()),thread, SLOT(quit()), Qt::QueuedConnection);
    QObject::connect(worker, SIGNAL(finished()),worker, SLOT(deleteLater()), Qt::QueuedConnection);
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()), Qt::QueuedConnection);
    thread->start();
}


void Streamer::streamModelToDiskFinished(Model* m, unsigned long long id){
    //now set the pointer right...
}

void Streamer::streamModelFromDiskFinished(Model* m, unsigned long long id){

    Model * stored_m = id_model_map[id];
    m->set_data(*stored_m);
    *stored_m = *m;

    finished_model_list.push_back(stored_m);
}

void Streamer::streamThreadFinished(){
    ta->removeThread();
}

//EVENT TRANSMITTER  now AS SLOT
void Streamer::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}
