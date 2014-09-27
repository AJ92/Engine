#ifndef EVENTCOMPOSITEOBJECT_H
#define EVENTCOMPOSITEOBJECT_H


class CompositeObject;

class EventCompositeObject
{
public:
    EventCompositeObject(CompositeObject * co);
    ~EventCompositeObject();

    CompositeObject * getCompositeObject();
    void setCompositeObject(CompositeObject * co);

private:
    CompositeObject * co;
};

#endif // EVENTCOMPOSITEOBJECT_H
