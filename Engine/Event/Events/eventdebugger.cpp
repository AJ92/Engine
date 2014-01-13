#include "eventdebugger.h"

EventDebugger::EventDebugger(QString debugMessage) :
    Object(),
    debugMessage(debugMessage)
{

}

EventDebugger::~EventDebugger(){

}

QString EventDebugger::getDebugMessage(){
    return debugMessage;
}

void EventDebugger::setDebugMessage(QString debugMessage){
    this->debugMessage = debugMessage;
}
