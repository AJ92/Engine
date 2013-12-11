#include "event.h"

Event::Event(Types eventTypes) :
    Object(),
    types(eventTypes)
{

}

bool Event::isType(Types eventTypes){
    if(types == eventTypes){
        return true;
    }
    return false;
}

void Event::setString(QString string){
    this->string = string;
}

QString Event::getString(){
    return string;
}
