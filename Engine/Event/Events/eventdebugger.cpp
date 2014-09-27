#include "eventdebugger.h"

EventDebugger::EventDebugger(QString debugMessage) :
    debugMessage(debugMessage)
{

}

EventDebugger::EventDebugger(double debugValue) :
    debugValue(debugValue)
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

double EventDebugger::getDebugValue(){
    return debugValue;
}

void EventDebugger::setDebugValue(double debugValue){
    this->debugValue = debugValue;
}
