#ifndef COMPONENT_H
#define COMPONENT_H

#include "Object/object.h"
#include "Object/entity.h"
#include "Object/CompositionHelper.h"

class Entity;

class Component : public Object
{

public:
    Component();

    virtual void init() { }
    virtual void update(float mFT) { }
    //draw is atm not needed...
    //virtual void draw() { }
    virtual ~Component() { }

    Entity * getParent();
    void setParent(Entity * parentEntity);

private:
    Entity * entity;

};

#endif // COMPONENT_H
