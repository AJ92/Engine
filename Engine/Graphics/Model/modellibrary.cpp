#include "modellibrary.h"

ModelLibrary::ModelLibrary() :
    EventListener(),
    EventTransmitter()
{
    //default 2
    streamer = new Streamer(2);
}

ModelLibrary::ModelLibrary(int maxThreads, int reserved_space) :
    EventListener(),
    EventTransmitter()
{
    //set max Threads
    streamer = new Streamer(maxThreads);
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
    streamer->streamModelFromDisk(m);
    addModel(m);
    debugMessage("ModelLibrary: count " + QString::number(modelCount()));
    return m;
}

int ModelLibrary::modelCount(){
    return model_list.size();
}




//private
void ModelLibrary::addModel(Model * mdl){
    if(!containsModel(mdl)){
        debugMessage("ModelLibrary: adding");
        model_list.push_back(mdl);
    }
}

bool ModelLibrary::containsModel(Model * mdl) const{
    /*
    unsigned int i;
    for(i=0; i< model_list.size(); i++){
        if(mdl->equal(*model_list[i])){
            return true;
        }
    }
    */
    for (std::list<Model *>::const_iterator iterator = model_list.begin(), end = model_list.end(); iterator != end; ++iterator) {
        //std::cout << *iterator;

        Model * m = *iterator;
        if(*m == *mdl){
            return true;
        }
    }


    return false;
}

bool ModelLibrary::removeModel(Model * mdl){
    /*
    unsigned int i;
    for(i=0; i< model_list.size(); i++){
        if(*model_list[i] == *mdl){
            std::vector<Model *>::iterator it = model_list.begin() + i;
            model_list.erase(it);
            break;
        }
    }
    */

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
