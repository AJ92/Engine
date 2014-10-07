#include "eventcompositeobject.h"

#include "Object/compositeobject.h"

EventCompositeObject::EventCompositeObject(SP<CompositeObject> co)
{
    this->co = co;
}

EventCompositeObject::~EventCompositeObject(){

}

SP<CompositeObject> EventCompositeObject::getCompositeObject(){
    return co;
}

void EventCompositeObject::setCompositeObject(SP<CompositeObject> co){
    this->co = co;
}
