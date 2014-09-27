#include "eventcompositeobject.h"

#include "Object/compositeobject.h"

EventCompositeObject::EventCompositeObject(CompositeObject * co)
{
    this->co = co;
}

EventCompositeObject::~EventCompositeObject(){

}

CompositeObject * EventCompositeObject::getCompositeObject(){
    return co;
}

void EventCompositeObject::setCompositeObject(CompositeObject * co){
    this->co = co;
}
