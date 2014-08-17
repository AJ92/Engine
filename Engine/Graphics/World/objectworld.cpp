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


void ObjectWorld::initialize(){

}


//EVENT LISTENER
//do not invoke the parents method...
void ObjectWorld::eventRecieved(Event e){
    if(e.type == Event::EventModelStreamedFromDisk){
        /*
        addModel(e.streamer->getModel());
        //check if some models actually got instanced during the time this model was loading...
        //and assign the new model data to them...
        updateInstances(e.streamer->getModel());
        */
    }
}

//EVENT TRANSMITTER
void ObjectWorld::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}
