#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Components/gameobject.h"
#include "Graphics/Renderer/renderer.h"

class GameObject;

class GraphicsComponent : public Object
{
public:
    virtual ~GraphicsComponent() {}
    virtual void update(GameObject &gameobject , Renderer &renderer) = 0;
};

#endif // GRAPHICSCOMPONENT_H
