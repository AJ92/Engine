#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "Debug/Ui/debugwindow.h"
#include "Event/eventlistener.h"

class Event;

class Debugger : public EventListener
{
public:
    Debugger();
    virtual void eventRecieved(Event e);

private:
    DebugWindow dw;
};

#endif // DEBUGGER_H
