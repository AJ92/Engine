#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Components/gameobject.h"

class GameObject;

class GraphicsComponent
{
public:
    virtual ~GraphicsComponent() {}
    virtual void update(GameObject &gameobject) = 0;
};

#endif // GRAPHICSCOMPONENT_H
