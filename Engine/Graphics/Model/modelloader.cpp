#include "modelloader.h"

#include "Event/event.h"

ModelLoader::ModelLoader(ThreadAccountant * ta) :
    EventListener(),
    EventTransmitter(),
    ta(ta)
{
    //set max Threads
    streamer = new Streamer(ta);
}

void ModelLoader::initialize(){
    debugMessage("modelloader initializing...");

    //stuff here
    streamer->addListener(this);
    streamer->initialize();

    debugMessage("modelloader initialized.");
}

//public
QList<Model *> ModelLoader::getModels() const{
    return model_list;
}

Model* ModelLoader::loadModel(QString path){
    Model * m = new Model();
    m->set_path(path);

    //compair the paths (has this the same model data? instance it!)
    Model * instance_from = containsModelData(m);
    if(instance_from != 0){
        //we found one, instance it!
        debugMessage("instancing...");
        m->instance_from(*instance_from);
        if(m->isReadyToRender()){
            //if the model was already loaded from the disk sort it in
            addModel(m);
        }
        else{
            //add it to the instances_to_load_list so it get's sorted in as soon as it's loaded
            addModelInstanceToLoad(m);
        }
    }
    else{
        //load the data, the model isn't in the library
        debugMessage("loading...");
        streamer->streamModelFromDisk(m);
        addModelUnique(m);
    }
    return m;
}

int ModelLoader::modelCount(){
    return model_list.size();
}

void ModelLoader::setModelsPerThread(int model_count){
    streamer->setModelsPerThread(model_count);
}

void ModelLoader::debugModelData(){
    debugMessage("ModelLoader Debug...");
    //will follow soon...
}




//private
//add the model to the model list (contains also instances)
void ModelLoader::addModel(Model * mdl){
    if(!containsModel(mdl)){
        model_list.push_back(mdl);
    }
}

//add the model to the unique model list (does not contain instances)
void ModelLoader::addModelUnique(Model * mdl){
    //do not check if there are instances, cause we know there is a base we instanced from!
    unique_model_list.push_back(mdl);
    unique_model_path_list.push_back(mdl->get_path());
    instances_to_load_list.append(QList<Model*>());
}

void ModelLoader::addModelInstanceToLoad(Model * mdl){
    for(int i = 0; i < unique_model_path_list.size(); i++){
        //get the right index to sort it in
        if(unique_model_path_list.at(i).compare(mdl->get_path()) == 0){
            instances_to_load_list[i].push_back(mdl);
            return;
        }
    }
    debugMessage("ModelLibrary::addModelInstanceToLoad: could not sort in the instance: " +
                 mdl->get_path());
}

void ModelLoader::updateInstances(Model * mdl){
    for(int i = 0; i < unique_model_path_list.size(); i++){
        //get the right index to sort it in
        if(unique_model_path_list.at(i).compare(mdl->get_path()) == 0){
            //update all instances and sort them in correctly to render
            for(int j = 0; j < instances_to_load_list.at(i).size(); j++){
                Model * m = instances_to_load_list.at(i).at(j);
                m->instance_from(*mdl);

                if(m->getParentCompositeObject() == 0){
                    qDebug("[WARNING] ModelLoader::updateInstances(Model * mdl) : no CompositeObject parent reference in model...");
                }

                addModel(m);
            }
            instances_to_load_list[i].clear();
        }
    }
}



Model * ModelLoader::containsModelData(Model * mdl){
    QList<Model *>::iterator i;
    for (i = unique_model_list.begin(); i != unique_model_list.end(); ++i){
        Model * m = *i;
        if((*m).equalData(*mdl)){
            return m;
        }
    }
    return 0;
}

Model * ModelLoader::containsModel(Model * mdl){
    QList<Model *>::iterator i;
    for (i = model_list.begin(); i != model_list.end(); ++i){
        Model * m = *i;
        if(*m == *mdl){
            return m;
        }
    }
    return 0;
}

bool ModelLoader::removeModel(Model * mdl){
    QList<Model *>::iterator i;
    int j = 0;
    for (i = model_list.begin(); i != model_list.end(); ++i){
        Model * m = *i;
        if(*m == *mdl){
            model_list.removeAt(j);
            return true;
        }
        j++;
    }

    //model not even loaded yet!
    return false;
}


//EVENT LISTENER
//do not invoke the parents method...
void ModelLoader::eventRecieved(Event e){
    if(e.type == Event::EventModelStreamedFromDisk){
        addModel(e.streamer->getModel());
        //check if some models actually got instanced during the time this model was loading...
        //and assign the new model data to them...
        updateInstances(e.streamer->getModel());
    }
}

//EVENT TRANSMITTER
void ModelLoader::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}

