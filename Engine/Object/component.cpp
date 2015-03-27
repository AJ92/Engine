#include "component.h"

Component::Component() :
    Object()
{
    //do nothing actually..
}

Entity * Component::getParent(){
    return entity;
}

void Component::setParent(Entity * parentEntity){
    this->entity = parentEntity;
}
