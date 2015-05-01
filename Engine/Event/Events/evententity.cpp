#include "evententity.h"

EventEntity::EventEntity(SP<Entity> entity)
{
    this->entity = entity;
}

EventEntity::~EventEntity(){

}

SP<Entity> EventEntity::getEntity(){
    return entity;
}

void EventEntity::setEntity(SP<Entity> entity){
    this->entity = entity;
}
