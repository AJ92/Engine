#include "compositeobject.h"

#include "Graphics/Model/model.h"
#include "Graphics/Model/light.h"
#include "Object/positation.h"

CompositeObject::CompositeObject() :
    Object(),
    name_("Empty")

{
}

CompositeObject::CompositeObject(QString name) :
    Object(),
    name_(name)
{
}



void CompositeObject::setModel(Model * model){
    model_ = model;
    type_ = type_ | ObjectModel; //binary or
}

void CompositeObject::setLight(Light * light){
    light_ = light;
    type_ = type_ | ObjectLight; //binary or
}

void CompositeObject::setPositation(Positation * positation){
    positation_ = positation;
    type_ = type_ | ObjectPositionRotation; //binary or
}



bool CompositeObject::hasModel(){
    if((type_ & ObjectModel) == ObjectModel){ //binary and
        return true;
    }
    return false;
}

bool CompositeObject::hasLight(){
    if((type_ & ObjectLight) == ObjectLight){ //binary and
        return true;
    }
    return false;
}

bool CompositeObject::hasPositation(){
    if((type_ & ObjectPositionRotation) == ObjectPositionRotation){ //binary and
        return true;
    }
    return false;
}



Model * CompositeObject::getModel(){
    return model_;
}

Light * CompositeObject::getLight(){
    return light_;
}

Positation * CompositeObject::getPositation(){
    return positation_;
}
