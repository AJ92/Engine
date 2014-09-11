#ifndef LOCATIONCOMPONENT_H
#define LOCATIONCOMPONENT_H

#include "Components/gameobject.h"

class GameObject;

class LocationComponent
{
public:
    virtual ~LocationComponent() {}
    virtual void update(GameObject &gameobject) = 0;
};

#endif // LOCATIONCOMPONENT_H
