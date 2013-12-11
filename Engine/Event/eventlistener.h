#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "Object/object.h"
#include "Event/event.h"

class EventListener : public Object
{
public:
    EventListener();
    virtual void eventRecieved(Event e);
};

#endif // EVENTLISTENER_H
