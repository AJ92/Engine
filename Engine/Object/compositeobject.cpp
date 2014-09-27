#include "compositeobject.h"

#include "Graphics/Model/model.h"
#include "Graphics/Model/light.h"
#include "Object/positation.h"

#include "Event/event.h"

CompositeObject::CompositeObject() :
    EventListener(),
    EventTransmitter(),
    name_("Empty")

{
    model_ = 0;
    light_ = 0;
    positation_ = 0;
}

CompositeObject::CompositeObject(QString name) :
    EventListener(),
    EventTransmitter(),
    name_(name)
{
    model_ = 0;
    light_ = 0;
    positation_ = 0;
}



void CompositeObject::setModel(Model * model){
    if(model_ != 0){
        model->removeListener(this);
    }
    model_ = model;
    //model_->setParentCompositeObject(this);
    type_ = type_ | ObjectModel; //binary or


    if(model_->isReadyToRender()){
        Event e;
        e.type = Event::EventCompositeObjectModelLoaded;
        e.compositeObject = new EventCompositeObject(this);
        this->transmit(e);
    }


    //model should send if it is loaded... but it probably won't so...
    model_->addListener(this);
}

void CompositeObject::setLight(Light * light){
    light_ = light;
    type_ = type_ | ObjectLight; //binary or
}

void CompositeObject::setPositation(Positation * positation){
    if(positation_ != 0){
        positation_->removeListener(this);
    }
    positation_ = positation;
    type_ = type_ | ObjectPositionRotation; //binary or
    positation_->addListener(this);
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




//EVENT LISTENER
//do not invoke the parents method...
void CompositeObject::eventRecieved(Event e){
    if(e.type == Event::EventModelLoaded){
        Event e;
        e.type = Event::EventCompositeObjectModelLoaded;
        e.compositeObject = new EventCompositeObject(this);
        this->transmit(e);
    }
}

void CompositeObject::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}
