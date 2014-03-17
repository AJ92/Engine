#include "event.h"

//not sure if even needed....

Event::Event() :
    Object()
{

}

//destroy pointers !!! currently not working...
Event::~Event(){
    switch (type)
    {
    case EventNone:
        break;
    case EventDebuggerMessage:
        //delete the EventDebugger pointer object!!!
        //delete debugger;
        break;
    case EventDebuggerShow:
        //no pointers for this type ... nothing to delete
        break;
    case EventDebuggerHide:
        //no pointers for this type ... nothing to delete
        break;
    case EventModelStreamedFromDisk:
        break;
    }
}

//should be replaced by a propper destructor or so ...
void Event::destroy(){
    switch (type)
    {
    case EventNone:
        break;
    case EventDebuggerMessage:
        //delete the EventDebugger pointer object!!!
        delete debugger;
        break;
    case EventDebuggerShow:
        //no pointers for this type ... nothing to delete
        break;
    case EventDebuggerHide:
        //no pointers for this type ... nothing to delete
        break;
    case EventModelStreamedFromDisk:
        delete streamer;
        break;
    }
}
