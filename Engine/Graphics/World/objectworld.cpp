#include "objectworld.h"
#include "Event/event.h"
#include "Object/compositeobject.h"
#include "Object/positation.h"

ObjectWorld::ObjectWorld(ThreadAccountant * ta) :
    EventListener(),
    EventTransmitter()
{
    this->ta = ta;
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
}


OctTree * ObjectWorld::getOctTree(){
    return ot;
}


CompositeObject * ObjectWorld::loadModelobject(QString name, QString path){
    CompositeObject * co = new CompositeObject(name);
    //randomized pos, for octtree test
    Positation * posi = new Positation();
    posi->set_position((double)((rand() & 2000)-1000),
                      (double)((rand() & 2000)-1000),
                      (double)((rand() & 2000)-1000));

    posi->set_scale(3.0,3.0,3.0);
    co->setPositation(posi);



    co->addListener(this);
    co->setModel(this->loadModel(path));


    //is handled now by events....
    //ot->addModel(co);


    //debugMessage(ot->debug_string());
    return co;
}

CompositeObject * ObjectWorld::loadModelobject(QString name, QString path, Positation * posi){
    CompositeObject * co = new CompositeObject(name);
    co->setPositation(posi);

    co->addListener(this);
    co->setModel(this->loadModel(path));

    return co;
}





//private stuff...
Model* ObjectWorld::loadModel(QString path){
    if(ml){
        //debugMessage("ObjectWorld::loadModel(path) : " + path);
        return ml->loadModel(path);
    }
    debugMessage("ModelLoader wasn't set up... it's useless to load Models yet!");
    return new Model();
}


void ObjectWorld::addModelToOctTree(CompositeObject * co){
    ot->addModel(co);
}


//EVENT LISTENER
//do not invoke the parents method...
void ObjectWorld::eventRecieved(Event e){
    if(e.type == Event::EventCompositeObjectModelLoaded){
        ot->addModel(e.compositeObject->getCompositeObject());
    }
}

//EVENT TRANSMITTER
void ObjectWorld::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}
