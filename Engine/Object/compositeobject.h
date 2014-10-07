#ifndef COMPOSITEOBJECT_H
#define COMPOSITEOBJECT_H

#include "Object/object.h"
#include <QString>
#include "Event/eventtransmitter.h"
#include "Event/eventlistener.h"
#include "Object/SmartPointer/smartpointer.h"

class Model;
class Light;
class Positation;
class Event;

class CompositeObject : virtual public EventListener, virtual public EventTransmitter
{
public:


    //extend to 32 bit if needed... ( 0xFFFFFFFF)
    enum ObjectType {

        ObjectEmpty             = 0x0000,

        ObjectPositionRotation  = 0x0001,

        ObjectModel             = 0x0002,
        ObjectPhysics           = 0x0004,
        ObjectInput             = 0x0008,
        ObjectLight             = 0x0010,

        ObjectCamera            = 0x0020,

        ObjectError             = 0xFFFF
        //more to follow...
    };

    enum ObjectMovementType {
        MovementStatic  = 0x0000,
        MovementDynamic = 0x0001
    };


    CompositeObject();
    CompositeObject(QString name, ObjectMovementType movementType);

    void setModel(SP<Model> model);
    void setLight(SP<Light> light);
    void setPositation(SP<Positation> positation);

    bool hasModel();
    bool hasLight();
    bool hasPositation();

    SP<Model> getModel();
    SP<Light> getLight();
    SP<Positation> getPositation();

    ObjectMovementType getObjectMovementType();

private:

    SP<CompositeObject> me_;
    SP<EventListener> me_eventListener_;

    QString name_;
    int type_;
    ObjectMovementType movementType_;

    SP<Model> model_;
    SP<Light> light_;
    SP<Positation> positation_;


    void debugMessage(QString message);
    void eventRecieved(Event e);
};

#endif // COMPOSITEOBJECT_H
