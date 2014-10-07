#include "modelloader.h"

#include "Event/event.h"

ModelLoader::ModelLoader(SP<ThreadAccountant> ta) :
    EventListener(),
    EventTransmitter(),
    ta(ta)
{
    //set max Threads
    streamer = SP<Streamer>(new Streamer(ta));
}

void ModelLoader::initialize(){
    debugMessage("modelloader initializing...");

    //stuff here
    streamer->addListener(this);
    streamer->initialize();

    debugMessage("modelloader initialized.");
}

//public
QList<SP<Model> > ModelLoader::getModels() const{
    return all_models_list;
}

void ModelLoader::loadModel(SP<Model> m){
    //compair the paths (has this the same model data? instance it!)



    SP<Model> instance_from = containsModelData(m);
    if(instance_from != 0){
        //we found one, instance it!
        //debugMessage("instancing...");
        m->instance_from(*instance_from);
        if(m->isReadyToRender()){
            //if the model was already loaded from the disk sort it in
            addModel(m);


            //transmit an event so the composite object knows that it's model is loaded!
            Event e;
            e.type = Event::EventModelLoaded;
            e.streamer = SP<EventStreamer>(new EventStreamer(m));
            m->transmit(e);

        }
        else{
            //add it to the instances_to_load_list so it get's sorted in as soon as it's loaded
            addModelInstanceToLoad(m);
        }
    }
    else{
        //load the data, the model isn't in the library
        //debugMessage("loading...");
        streamer->streamModelFromDisk(m);
        addModelUnique(m);
    }
    return;
}

int ModelLoader::modelCount(){
    return all_models_list.size();
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
void ModelLoader::addModel(SP<Model> mdl){
    if(containsModel(mdl) != 0){
        all_models_list.push_back(mdl);
    }
}

//add the model to the unique model list (does not contain instances)
void ModelLoader::addModelUnique(SP<Model> mdl){
    //do not check if there are instances, cause we know there is a base we instanced from!
    unique_models_list.push_back(mdl);
    unique_model_paths_list.push_back(mdl->get_path());
    instances_to_load_list.append(QList<SP<Model> >());
}

void ModelLoader::addModelInstanceToLoad(SP<Model> mdl){
    for(int i = 0; i < unique_model_paths_list.size(); i++){
        //get the right index to sort it in
        if(unique_model_paths_list.at(i).compare(mdl->get_path()) == 0){
            instances_to_load_list[i].push_back(mdl);
            return;
        }
    }
    debugMessage("ModelLibrary::addModelInstanceToLoad: could not sort in the instance: " +
                 mdl->get_path());
}

void ModelLoader::updateInstances(SP<Model> mdl){
    for(int i = 0; i < unique_model_paths_list.size(); i++){
        //get the right index to sort it in
        if(unique_model_paths_list[i].compare(mdl->get_path()) == 0){
            //update all instances and sort them in correctly to render
            for(int j = 0; j < instances_to_load_list.at(i).size(); j++){
                SP<Model> m = instances_to_load_list.at(i).at(j);
                m->instance_from(*mdl);
                addModel(m);


                //give the compositeobject a notification...
                //the model is loaded...
                Event e;
                e.type = Event::EventModelLoaded;
                e.streamer = SP<EventStreamer>(new EventStreamer(m));
                m->transmit(e);
            }
            instances_to_load_list[i].clear();
        }
    }
}



SP<Model> ModelLoader::containsModelData(SP<Model> mdl){
    QList<SP<Model> >::iterator i;
    for (i = unique_models_list.begin(); i != unique_models_list.end(); ++i){
        SP<Model> m = *i;
        if((*m).equalData(*mdl)){
            return m;
        }
    }
    return SP<Model>();
}

SP<Model> ModelLoader::containsModel(SP<Model> mdl){
    QList<SP<Model> >::iterator i;
    for (i = all_models_list.begin(); i != all_models_list.end(); ++i){
        SP<Model> m = *i;
        if(*m == *mdl){
            return m;
        }
    }
    return SP<Model>();
}

bool ModelLoader::removeModel(SP<Model> mdl){
    QList<SP<Model> >::iterator i;
    int j = 0;
    for (i = all_models_list.begin(); i != all_models_list.end(); ++i){
        SP<Model> m = *i;
        if(*m == *mdl){
            all_models_list.removeAt(j);
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

