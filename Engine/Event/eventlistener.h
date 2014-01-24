#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "Object/object.h"
#include "Event/event.h"

#include <queue>

class EventListener : public Object
{
public:
    EventListener();
    virtual void eventRecieved(Event e);
    Event getEvent();

private:
    std::queue<Event> event_queue;

};

#endif // EVENTLISTENER_H
