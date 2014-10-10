#include "objectworld.h"
#include "Event/event.h"
#include "Object/compositeobject.h"
#include "Object/positation.h"
#include "Graphics/Model/light.h"

ObjectWorld::ObjectWorld(SP<ThreadAccountant> ta) :
    EventListener(),
    EventTransmitter()
{
    this->ta = ta;

    count_models_in = 0;
    count_models_out = 0;

    me_eventListener = SP<EventListener> (this);
}

ObjectWorld::~ObjectWorld(){
    //DESTRUCTOR... soon
}

void ObjectWorld::setModelLoader(SP<ModelLoader> ml){
    this->ml = ml;
}

void ObjectWorld::setModelsPerThread(int model_count){
    ml->setModelsPerThread(model_count);
}

void ObjectWorld::setLightModelPath(QString path){
    light_model_path = path;
}

void ObjectWorld::initialize(){
    ml->addListener(me_eventListener);
    ml->initialize();

    ot = SP<OctTree>(new OctTree(64));

    ot_dynamic_model = SP<OctTreeFast>(new OctTreeFast(10));
    ot_dynamic_lights = SP<OctTreeFast>(new OctTreeFast(10));


    //preload the light model...
    // maybe in a later version of the engine generate the light mesh....
    light_model = SP<Model>(new Model());
    light_model->set_path(light_model_path);
    loadModel(light_model);
}


SP<OctTree> ObjectWorld::getOctTree(){
    return ot;
}

SP<OctTreeFast> ObjectWorld::getOctTreeFastDynamicModels(){
    return ot_dynamic_model;
}

SP<OctTreeFast> ObjectWorld::getOctTreeFastDynamicLights(){
    return ot_dynamic_lights;
}


//dynamic light
SP<CompositeObject> ObjectWorld::loadLightobject(QString name){
    SP<CompositeObject> co(new CompositeObject(name, CompositeObject::MovementDynamic));
    //randomized pos, for octtree test
    //they won't land by default in the same node and the octtree won't
    //grow in depth that fast ...
    SP<Positation> posi(new Positation());
    posi->set_position((double)((rand() & 1000)-500),
                       (double)((rand() & 1000)-500),
                       (double)((rand() & 1000)-500));

    co->setPositation(posi);

    SP<Light> light(new Light());
    co->setLight(light);

    co->addListener(me_eventListener);

    SP<Model> light_mdl(new Model());
    light_mdl->set_path(light_model_path);

    co->setModel(light_mdl);
    this->loadModel(light_mdl);

    count_models_in += 1;

    all_comp_objs.append(co);

    return co;
}


//dynamic
SP<CompositeObject> ObjectWorld::loadModelobject(QString name, QString path){
    SP<CompositeObject> co(new CompositeObject(name, CompositeObject::MovementDynamic));
    //randomized pos, for octtree test
    //they won't land by default in the same node and the octtree won't
    //grow in depth that fast ...
    SP<Positation> posi(new Positation());
    posi->set_position((double)((rand() & 1000)-500),
                      (double)((rand() & 1000)-500),
                      (double)((rand() & 1000)-500));

    co->setPositation(posi);

    co->addListener(me_eventListener);
    SP<Model> m(new Model());
    m->set_path(path);
    co->setModel(m);
    this->loadModel(m);

    count_models_in += 1;

    all_comp_objs.append(co);

    return co;
}

//static
SP<CompositeObject> ObjectWorld::loadModelobject(QString name, QString path, SP<Positation> posi){
    SP<CompositeObject> co(new CompositeObject(name, CompositeObject::MovementStatic));



    co->setPositation(posi);

    co->addListener(me_eventListener);
    SP<Model> m(new Model());
    m->set_path(path);
    co->setModel(m);
    this->loadModel(m);

    all_comp_objs.append(co);

    return co;
}





//private stuff...
void ObjectWorld::loadModel(SP<Model> m){
    //test for nullpointer...
    //better said if the smartpointer has a pointer...
    if(ml != 0){
        //debugMessage("ObjectWorld::loadModel(Model * m);;
        ml->loadModel(m);
        return;
    }
    debugMessage("ModelLoader wasn't set up... it's useless to load Models yet!");
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
        SP<CompositeObject> obj = e.compositeObject->getCompositeObject();
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


                //count_models_out += 1;
                /*
                debugMessage("ObjectWorld : dyn_object in/out:  " +
                             QString::number(count_models_in) + " / " +
                             QString::number(count_models_out) + " ... " +
                             QString::number(obj->getAllListeners().size()));
                */
                return;
            }
            if(obj->getObjectMovementType() == CompositeObject::MovementStatic){
                debugMessage("static...");
                ot->addModel(obj);
                return;
            }
        }
    }
}

//EVENT TRANSMITTER
void ObjectWorld::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = SP<EventDebugger>(new EventDebugger(message));
    this->transmit(e);
}
