#include "objectworld.h"
#include "Event/event.h"
#include "Object/compositeobject.h"
#include "Object/positation.h"

ObjectWorld::ObjectWorld(ThreadAccountant * ta) :
    EventListener(),
    EventTransmitter()
{
    this->ta = ta;

    count_models_in = 0;
    count_models_out = 0;
}

ObjectWorld::~ObjectWorld(){
    //DESTRUCTOR... soon
}

void ObjectWorld::setModelLoader(ModelLoader * ml){
    this->ml = ml;
}

void ObjectWorld::setModelsPerThread(int model_count){
    if(ml){
        ml->setModelsPerThread(model_count);
    }
}

void ObjectWorld::initialize(){
    ml->addListener(this);
    ml->initialize();

    ot = new OctTree(200);

    ot_dynamic_model = new OctTreeFast(200);
    ot_dynamic_lights = new OctTreeFast(200);

}


OctTree * ObjectWorld::getOctTree(){
    return ot;
}

OctTreeFast * ObjectWorld::getOctTreeFastDynamicModels(){
    return ot_dynamic_model;
}

OctTreeFast * ObjectWorld::getOctTreeFastDynamicLights(){
    return ot_dynamic_lights;
}


//dynamic
CompositeObject * ObjectWorld::loadModelobject(QString name, QString path){
    CompositeObject * co = new CompositeObject(name, CompositeObject::MovementDynamic);
    //randomized pos, for octtree test
    //they won't land by default in the same node and the octtree won't
    //grow in depth that fast ...
    Positation * posi = new Positation();
    posi->set_position((double)((rand() & 1000)-500),
                      (double)((rand() & 1000)-500),
                      (double)((rand() & 1000)-500));

    co->setPositation(posi);

    co->addListener(this);
    Model * m = new Model();
    m->set_path(path);
    co->setModel(m);
    this->loadModel(m);

    count_models_in += 1;

    return co;
}

//static
CompositeObject * ObjectWorld::loadModelobject(QString name, QString path, Positation * posi){
    CompositeObject * co = new CompositeObject(name, CompositeObject::MovementStatic);
    co->setPositation(posi);

    co->addListener(this);
    Model * m = new Model();
    m->set_path(path);
    co->setModel(m);
    this->loadModel(m);

    return co;
}





//private stuff...
void ObjectWorld::loadModel(Model * m){
    if(ml){
        //debugMessage("ObjectWorld::loadModel(Model * m);;
        ml->loadModel(m);
        return;
    }
    debugMessage("ModelLoader wasn't set up... it's useless to load Models yet!");
}


void ObjectWorld::addModelToOctTree(CompositeObject * co){
    ot->addModel(co);
}


//EVENT LISTENER
//do not invoke the parents method...
void ObjectWorld::eventRecieved(Event e){

    /*
    QString debug_output =  "Ow  ID: " + QString::number(this->EventTransmitter::id()) +
                            "   Event: " + QString::number(e.type);
    qDebug(debug_output.toUtf8());
    */

    if(e.type == Event::EventCompositeObjectModelLoaded){
        CompositeObject * obj = e.compositeObject->getCompositeObject();
        //dispatch to correct tree
        if(obj->hasLight()){
            debugMessage("light...");
            //add it to the light dynamic tree...
            ot_dynamic_lights->addCompositeObject(obj);
            return;
        }
        else{
            //has no light... but should have a model
            if(obj->getObjectMovementType() == CompositeObject::MovementDynamic){
                debugMessage("dynamic...");
                ot_dynamic_model->addCompositeObject(obj);
                count_models_out += 1;

                debugMessage("ObjectWorld : dyn_object in/out:  " +
                             QString::number(count_models_in) + " / " +
                             QString::number(count_models_out) + " ... " +
                             QString::number(obj->getAllListeners().size()));

                return;
            }
            if(obj->getObjectMovementType() == CompositeObject::MovementStatic){
                debugMessage("static...");
                ot->addModel(e.compositeObject->getCompositeObject());
                return;
            }
        }
    }
}

//EVENT TRANSMITTER
void ObjectWorld::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}
