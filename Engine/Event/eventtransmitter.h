#ifndef EVENTTRANSMITTER_H
#define EVENTTRANSMITTER_H


#include "Object/object.h"

//#include "Event/event.h"
//#include "Event/eventlistener.h"


#include <vector>
//#include <algorithm>

#include "Object/SmartPointer/smartpointer.h"


#include <QDebug>

class EventListener;
class Event;

class EventTransmitter : public Object
{
public:
    EventTransmitter();
    EventTransmitter(int reserved_space);

    //WE USE POINTER FOR PROPPER INHERITANCE
    virtual void addListener(SP<EventListener> el);
    virtual bool containsListener(SP<EventListener> el);
    virtual void removeListener(SP<EventListener> el);

    virtual void transmit(Event e);
    virtual void debugMessage(QString message);

    virtual std::vector<SP<EventListener> > getAllListeners() const;
    virtual void setListeners(std::vector<SP<EventListener> > listeners);

private:

    std::vector<SP<EventListener> > listeners;

};

#endif // EVENTTRANSMITTER_H
