#ifndef COMPOSITEOBJECT_H
#define COMPOSITEOBJECT_H

#include "Object/object.h"
#include <QString>

class Model;
class Light;
class Positation;

class CompositeObject : public Object
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


    CompositeObject();
    CompositeObject(QString name);

    void setModel(Model * model);
    void setLight(Light * light);
    void setPositation(Positation * positation);

    bool hasModel();
    bool hasLight();
    bool hasPositation();

    Model * getModel();
    Light * getLight();
    Positation * getPositation();

private:
    QString name_;
    int type_;

    Model * model_;
    Light * light_;
    Positation * positation_;
};

#endif // COMPOSITEOBJECT_H
