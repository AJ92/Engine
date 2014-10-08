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
    type_ = ObjectEmpty;
    movementType_ = MovementStatic;

    me_ = SP<CompositeObject>(this);
    me_eventListener_ = SP<EventListener>(this);
}

CompositeObject::CompositeObject(QString name, ObjectMovementType movementType) :
    EventListener(),
    EventTransmitter(),
    name_(name)
{
    type_ = ObjectEmpty;
    movementType_ = movementType;

    me_ = SP<CompositeObject>(this);
    me_eventListener_ = SP<EventListener>(this);
}



void CompositeObject::setModel(SP<Model> model){
    if(model_ != 0){
        model_->removeListener(me_eventListener_);
    }
    model_ = model;

    //model_->setParentCompositeObject(this);
    type_ = type_ | ObjectModel; //binary or

    //model should send if it is loaded... but it probably won't so...
    model_->addListener(me_eventListener_);
}

void CompositeObject::setLight(SP<Light> light){
    light_ = light;
    type_ = type_ | ObjectLight; //binary or
}

void CompositeObject::setPositation(SP<Positation> positation){
    if(positation_ != 0){
        positation_->removeListener(me_eventListener_);
    }

    if(hasPositation()){
        qDebug("CO old pos:");
        qDebug(QString::number(positation_->getPosition().x()).toUtf8());
        qDebug(QString::number(positation_->getPosition().y()).toUtf8());
        qDebug(QString::number(positation_->getPosition().z()).toUtf8());
    }

    positation_ = positation;
    type_ = type_ | ObjectPositionRotation; //binary or
    positation_->addListener(me_eventListener_);


    if(hasPositation()){
        qDebug("CO new pos:");
        qDebug(QString::number(positation_->getPosition().x()).toUtf8());
        qDebug(QString::number(positation_->getPosition().y()).toUtf8());
        qDebug(QString::number(positation_->getPosition().z()).toUtf8());
    }

    //scaled, because the spherical bound needs to be adjusted...
    Event e;
    e.type = Event::EventCompositeObjectScaled;
    positation_->transmit(e);

    Event e2;
    e2.type = Event::EventCompositeObjectMoved;
    positation_->transmit(e2);
    //e.compositeObject = SP<EventCompositeObject> (new EventCompositeObject(me_));
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



SP<Model> CompositeObject::getModel(){
    return model_;
}

SP<Light> CompositeObject::getLight(){
    return light_;
}

SP<Positation> CompositeObject::getPositation(){
    return positation_;
}


CompositeObject::ObjectMovementType CompositeObject::getObjectMovementType(){
    return movementType_;
}


//EVENT LISTENER
//do not invoke the parents method...
void CompositeObject::eventRecieved(Event e){
    if(e.type == Event::EventModelLoaded){

        //adjust the size
        if(hasPositation() && hasModel()){
            positation_->set_size(model_->get_size());
        }

        Event e2;
        e2.type = Event::EventCompositeObjectModelLoaded;
        e2.compositeObject = SP<EventCompositeObject> (new EventCompositeObject(me_));
        this->transmit(e2);
    }

    //forward the message...
    if((e.type == Event::EventCompositeObjectMoved) ||
       (e.type == Event::EventCompositeObjectRotated)){
        //forward the message...
        e.compositeObject = SP<EventCompositeObject> (new EventCompositeObject(me_));
        this->transmit(e);
    }

    if(e.type == Event::EventCompositeObjectScaled){
        if(hasPositation() && hasModel()){
            positation_->set_size(model_->get_size());
        }
        //forward the message...
        e.compositeObject = SP<EventCompositeObject> (new EventCompositeObject(me_));
        this->transmit(e);
    }

    /*
    QString debug_output =  "Co  ID: " + QString::number(this->EventTransmitter::id()) +
                            "   Event: " + QString::number(e.type) +
                            "   Listeners: "  + QString::number(this->getAllListeners().size());
    qDebug(debug_output.toUtf8());
    */
}

void CompositeObject::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = SP<EventDebugger> (new EventDebugger(message));
    this->transmit(e);
}
