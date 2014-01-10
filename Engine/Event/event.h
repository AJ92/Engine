#ifndef EVENT_H
#define EVENT_H

#include "Object/object.h"
#include <QString>

//include all Events
#include "Event/Events/eventdebugger.h"

class Event : public Object
{
public:

    Event();
    ~Event();

    void destroy();

    //EVENT TYPES SHOULD NOT BE COMBINED!!!
    enum EventType {
        EventDebuggerMessage        = 0x0000,
        EventDebuggerShow           = 0x0001,
        EventDebuggerHide           = 0x0002
        //more to follow...
    };


    //The event type.
    EventType type;

    union {
        EventDebugger *debugger;
        //more to follow...
    };


};

#endif // EVENT_H
