#ifndef EVENT_H
#define EVENT_H

#include "Object/object.h"
#include <QString>

//include all Events
#include "Event/Events/eventdebugger.h"
#include "Event/Events/eventstreamer.h"
#include "Event/Events/eventwindow.h"
#include "Event/Events/eventmodel.h"
#include "Event/Events/eventcompositeobject.h"

#include "Object/SmartPointer/smartpointer.h"

class Event : public Object
{
public:

    Event();
    virtual ~Event();

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
        EventModelRotated           = 0x0007,
        EventModelScaled            = 0x0008,
        EventModelLoaded            = 0x0009,
        EventModelRemoved           = 0x0010,
        EventModelDeleted           = 0x0011,

        EventCompositeObjectModelLoaded       = 0x0012,
        EventCompositeObjectMoved             = 0x0013,
        EventCompositeObjectRotated           = 0x0014,
        EventCompositeObjectScaled            = 0x0015,
        EventCompositeObjectLoaded            = 0x0016,
        EventCompositeObjectRemoved           = 0x0017,
        EventCompositeObjectDeleted           = 0x0018,



        EventDebuggerFPS                =0x1000,
        EventDebuggerNSPerFrame         =0x1001,
        EventDebuggerMeshsPerFrame      =0x1002,
        EventDebuggerTrianglesPerFrame  =0x1003,
        EventDebuggerTimeStep           =0x1004,
        EventDebuggerTexBindsPerFrame   =0x1005

        //more to follow...
    };


    //The event type.
    EventType type;


    SP<EventDebugger>           debugger;
    SP<EventStreamer>           streamer;  //streamer is same as model and will be removed one day...
    SP<EventWindow>             window;
    SP<EventModel>              model;
    SP<EventCompositeObject>    compositeObject;
    //more to follow...



};

#endif // EVENT_H
