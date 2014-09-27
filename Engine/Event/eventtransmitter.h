#ifndef EVENTTRANSMITTER_H
#define EVENTTRANSMITTER_H


#include "Object/object.h"

//#include "Event/event.h"
//#include "Event/eventlistener.h"


#include <vector>
//#include <algorithm>


#include <QDebug>

class EventListener;
class Event;

class EventTransmitter : public Object
{
public:
    EventTransmitter();
    EventTransmitter(int reserved_space);

    //WE USE POINTER FOR PROPPER INHERITANCE
    virtual void addListener(EventListener * el);
    virtual bool containsListener(EventListener * el);
    virtual void removeListener(EventListener * el);

    virtual void transmit(Event e);
    virtual void debugMessage(QString message);

    virtual std::vector<EventListener*> getAllListeners() const;
    virtual void setListeners(std::vector<EventListener*> listeners);

private:

    std::vector<EventListener*> listeners;

};

#endif // EVENTTRANSMITTER_H
