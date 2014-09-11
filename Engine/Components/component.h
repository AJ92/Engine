#ifndef COMPONENT_H
#define COMPONENT_H

//interface
class Component
{
public:
    virtual ~Component() {}
    virtual void update() = 0;

};

#endif // COMPONENT_H
