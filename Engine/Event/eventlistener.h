#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "Object/object.h"
//std needs the include...
#include "Event/event.h"

#include <queue>

class Event;

class EventListener : public Object
{
public:
    EventListener();
    ~EventListener();
    virtual void eventRecieved(Event e);
    Event getNextEvent();
    int getEventAmount();

private:
    std::queue<Event> event_queue;

};

#endif // EVENTLISTENER_H
