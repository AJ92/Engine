#include "modellibrary.h"

ModelLibrary::ModelLibrary(ThreadAccountant * ta) :
    EventListener(),
    EventTransmitter(),
    ta(ta)
{
    //set max Threads
    streamer = new Streamer(ta);
}

void ModelLibrary::initialize(){
    debugMessage("modellibrary initializing...");

    //stuff here
    streamer->addListener(this);
    streamer->initialize();

    debugMessage("modellibrary initialized.");
}

//public
std::list<Model *> ModelLibrary::getModels() const{
    return model_list;
}

Model* ModelLibrary::loadModel(QString path){
    Model * m = new Model();
    m->set_path(path);

    //compair the paths (has this the same model data? instance it!)
    Model * instance_from = containsModelData(m);
    if(instance_from != 0){
        //we found one, instance it!
        debugMessage("instancing...");
        m->instance_from(*instance_from);
    }
    else{
        //load the data, the model isn't in the library
        streamer->streamModelFromDisk(m);
        unique_model_list.push_back(m);
    }
    addModel(m);
    return m;
}

int ModelLibrary::modelCount(){
    return model_list.size();
}

void ModelLibrary::setModelsPerThread(int model_count){
    streamer->setModelsPerThread(model_count);
}




//private
void ModelLibrary::addModel(Model * mdl){
    if(!containsModel(mdl)){
        model_list.push_back(mdl);
    }
}

Model * ModelLibrary::containsModelData(Model * mdl){
    for (std::list<Model *>::const_iterator iterator = unique_model_list.begin(), end = unique_model_list.end(); iterator != end; ++iterator) {
        //std::cout << *iterator;

        Model * m = *iterator;
        if((*m).equalData(*mdl)){
            return m;
        }
    }
    return 0;
}

Model * ModelLibrary::containsModel(Model * mdl){
    for (std::list<Model *>::const_iterator iterator = model_list.begin(), end = model_list.end(); iterator != end; ++iterator) {
        //std::cout << *iterator;

        Model * m = *iterator;
        if(*m == *mdl){
            return m;
        }
    }
    return 0;
}

bool ModelLibrary::removeModel(Model * mdl){
    for (std::list<Model *>::iterator iterator = model_list.begin(), end = model_list.end(); iterator != end; ++iterator) {
        //std::cout << *iterator;

        Model * m = *iterator;
        if(*m == *mdl){
            model_list.erase(iterator);
            return true;
        }
    }

    //model not even loaded yet!
    return false;
}

//EVENT TRANSMITTER
void ModelLibrary::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}
