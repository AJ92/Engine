#include "event.h"

//not sure if even needed....

Event::Event()
{

}

//destroy pointers !!! currently not working...
Event::~Event(){
    switch (type)
    {
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
    }
}

//should be replaced by a propper destructor or so ...
void Event::destroy(){
    switch (type)
    {
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
    }
}
