#ifndef EVENT_H
#define EVENT_H

#include "Object/object.h"
#include <QString>

//include all Events
#include "Event/Events/eventdebugger.h"
#include "Event/Events/eventstreamer.h"

class Event : public Object
{
public:

    Event();
    ~Event();

    void destroy();

    //EVENT TYPES SHOULD NOT BE COMBINED!!!
    enum EventType {
        EventNone                   = 0x0000,
        EventDebuggerMessage        = 0x0001,
        EventDebuggerShow           = 0x0002,
        EventDebuggerHide           = 0x0003,
        EventModelStreamedFromDisk  = 0x0004
        //more to follow...
    };


    //The event type.
    EventType type;

    union {
        EventDebugger *debugger;
        EventStreamer *streamer;
        //more to follow...
    };


};

#endif // EVENT_H
