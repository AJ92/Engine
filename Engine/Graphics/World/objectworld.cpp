#include "objectworld.h"

ObjectWorld::ObjectWorld(ThreadAccountant * ta) :
    EventListener(),
    EventTransmitter()
{
    this->ta = ta;
}

ObjectWorld::~ObjectWorld(){
    //DESTRUCTOR... soon
}

void ObjectWorld::setModelLoader(ModelLoader * ml){
    this->ml = ml;
}

void ObjectWorld::setModelsPerThread(int model_count){
    if(ml){
        ml->setModelsPerThread(model_count);
    }
}

void ObjectWorld::initialize(){
    ml->addListener(this);
    ml->initialize();
}

Model* ObjectWorld::loadModel(QString path){
    if(ml){
        return ml->loadModel(path);
    }
    debugMessage("ModelLoader wasn't set up... it's useless to load Models yet!");
    return new Model();
}


//EVENT LISTENER
//do not invoke the parents method...
void ObjectWorld::eventRecieved(Event e){
    /*
    if(e.type == Event::EventModelStreamedFromDisk){

    }
    */
}

//EVENT TRANSMITTER
void ObjectWorld::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}
