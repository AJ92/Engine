#include "component.h"

Component::Component() :
    Object()
{
    //do nothing actually..
}

SP<Entity> Component::getParent(){
    return entity;
}

void Component::setParent(SP<Entity> parentEntity){
    this->entity = parentEntity;
}
