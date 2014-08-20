#ifndef EVENT_H
#define EVENT_H

#include "Object/object.h"
#include <QString>

//include all Events
#include "Event/Events/eventdebugger.h"
#include "Event/Events/eventstreamer.h"
#include "Event/Events/eventwindow.h"
#include "Event/Events/eventmodel.h"

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

        EventModelStreamedFromDisk  = 0x0004,

        EventWindowResize           = 0x0005,

        EventModelMoved             = 0x0006,
        EventModelLoaded            = 0x0007,
        EventModelRemoved           = 0x0008,
        EventModelDeleted           = 0x0009

        //more to follow...
    };


    //The event type.
    EventType type;

    //TODO:
    //this will be replaced by smart pointers soon...
    union {
        EventDebugger   *debugger;
        EventStreamer   *streamer;  //streamer is same as model and will be removed one day...
        EventWindow     *window;
        EventModel      *model;
        //more to follow...
    };


};

#endif // EVENT_H
