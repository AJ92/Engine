#ifndef EVENTENTITY_H
#define EVENTENTITY_H

#include "Object/SmartPointer/smartpointer.h"

class Entity;

class EventEntity
{
public:
    EventEntity(SP<Entity> entity);
    ~EventEntity();

    SP<Entity> getEntity();
    void setEntity(SP<Entity> entity);

private:
    SP<Entity> entity;
};

#endif // EVENTENTITY_H
