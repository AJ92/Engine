#ifndef EVENTCOMPOSITEOBJECT_H
#define EVENTCOMPOSITEOBJECT_H

#include "Object/SmartPointer/smartpointer.h"

class CompositeObject;

class EventCompositeObject
{
public:
    EventCompositeObject(SP<CompositeObject> co);
    ~EventCompositeObject();

    SP<CompositeObject> getCompositeObject();
    void setCompositeObject(SP<CompositeObject> co);

private:
    SP<CompositeObject> co;
};

#endif // EVENTCOMPOSITEOBJECT_H
