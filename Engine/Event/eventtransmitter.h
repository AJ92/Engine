#ifndef EVENTTRANSMITTER_H
#define EVENTTRANSMITTER_H


#include "Object/object.h"

#include "Event/event.h"
#include "Event/eventlistener.h"


#include <vector>
//#include <algorithm>


#include <QDebug>

class EventTransmitter : public Object
{
public:
    EventTransmitter();
    EventTransmitter(int reserved_space);

    virtual void addListener(EventListener el);
    virtual bool containsListener(EventListener el);
    virtual void removeListener(EventListener el);

    virtual void transmit(Event e);

private:

    std::vector<EventListener> listeners;

};

#endif // EVENTTRANSMITTER_H