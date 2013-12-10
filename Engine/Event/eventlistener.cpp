#include "eventlistener.h"

EventListener::EventListener() :
    Object()
{
}


void EventListener::eventRecieved(Event e){
    //override this class...
    qDebug("event recieved!");
}
