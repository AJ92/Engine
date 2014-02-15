#include "eventtransmitter.h"

EventTransmitter::EventTransmitter() :
    Object()
{
    //reserve room for 5 event listeners
    listeners.reserve(5);
}

EventTransmitter::EventTransmitter(int reserved_space) :
    Object()
{
    //reserve room for event listeners
    listeners.reserve(reserved_space);
}

void EventTransmitter::addListener(EventListener * el){
    if(!containsListener(el)){
        listeners.push_back(el);
    }
}

bool EventTransmitter::containsListener(EventListener * el){

    //contains    needs algorithm, ~ o(n)
    /*
    if(std::find(listeners.begin(), listeners.end(), el) != listeners.end()){
        qDebug("is here");
    }
    else{
        qDebug("not here");
    }
    */


    unsigned int i;
    for(i=0; i< listeners.size(); i++){
        if(el->equal(*listeners[i])){
            return true;
        }
    }
    return false;
}

void EventTransmitter::removeListener(EventListener * el){

    unsigned int i;
    for(i=0; i< listeners.size(); i++){
        if(listeners[i] == el){
            std::vector<EventListener*>::iterator it = listeners.begin() + i;
            listeners.erase(it);
            break;
        }
    }
}

void EventTransmitter::transmit(Event e){
    unsigned int i;
    for(i=0; i< listeners.size(); i++){
        listeners[i]->eventRecieved(e);
    }
}

//EVENT TRANSMITTER
void EventTransmitter::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}
