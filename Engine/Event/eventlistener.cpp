#include "eventlistener.h"


EventListener::EventListener() :
    Object()
{
}

//inherit from this class and implement the eventRecieved
//function as override or use getEvent function to check for events.
void EventListener::eventRecieved(Event e){
    event_queue.push(e);
}

Event EventListener::getNextEvent(){
    Event e;
    if(event_queue.size() > 0){
        e = event_queue.front();
        event_queue.pop();
    }
    else{
        e.type = Event::EventNone;
    }
    return e;
}

int EventListener::getEventAmount(){
    return event_queue.size();
}
