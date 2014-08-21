#include "lightlibrary.h"

#include "Graphics/Model/model.h"
#include "Graphics/Model/Components/material.h"
#include "Graphics/Model/Components/mesh.h"
#include "Graphics/Model/light.h"

#include "Event/event.h"


LightLibrary::LightLibrary(ThreadAccountant * ta) :
    EventListener(),
    EventTransmitter(),
    ta(ta)
{
    //set max Threads
    streamer = new Streamer(ta);
}




void LightLibrary::initialize(){
    debugMessage("lightlibrary initializing...");

    //stuff here
    streamer->addListener(this);
    streamer->initialize();

    debugMessage("lightlibrary initialized.");
}

//public
QList<Light *> LightLibrary::getLights() const{
    return light_list;
}

Light* LightLibrary::loadLight(QString path){

    //build an empty light
    Model * m = new Model();
    m->set_path(path);

    Light * l = new Light();
    l->set_model_data(m);


    //compair the paths (has this the same light/model data? instance it!)
    Light * l_instance_from = containsLightData(l);
    if(l_instance_from != 0){
        //we found one, instance it!
        debugMessage("instancing light...");
        l->instance_from(*l_instance_from);
        if(l->isReadyToRender()){
            //if the model was already loaded from the disk sort it in
            debugMessage("adding...");
            addLight(l);
        }
        else{
            //add it to the instances_to_load_list so it get's sorted in as soon as it's loaded
            debugMessage("need to load...");
            addLightInstanceToLoad(l);
        }
    }
    else{
        //load the data, the model isn't in the library
        debugMessage("loading light...");
        streamer->streamModelFromDisk(m);
        addLightUnique(l);

        //add them to temporary lists so we can set both back together after loading...
        light_loading.append(l);
        model_loading.append(m);
    }

    return l;
}

int LightLibrary::lightCount(){
    return light_list.size();
}

void LightLibrary::setLightsPerThread(int light_count){
    streamer->setModelsPerThread(light_count);
}


QList<QList<Mesh*> > LightLibrary::getMeshModelList(){
    return mesh_model_list;
}

QList<QList<Model*> > LightLibrary::getModelMeshList(){
    return model_mesh_list;
}

QList<QList<Light*> > LightLibrary::getLightMeshList(){
    return light_mesh_list;
}

QList<Material*> LightLibrary::getMaterialMeshList(){
    return material_mesh_list;
}


void LightLibrary::debugLightModelData(){
    debugMessage("LightLibrary Debug:");
    for(int i = 0; i < material_mesh_list.size(); i++){
        debugMessage("Mtl: " + material_mesh_list[i]->get_name() +
                     QString::number(material_mesh_list[i]->id()));
        for(int j = 0; j < mesh_model_list[i].size(); j++){
            debugMessage(" - Mesh: " + mesh_model_list[i].at(j)->get_name() +
                         QString::number(mesh_model_list[i].at(j)->id()) +
                         "   " + model_mesh_list[i].at(j)->get_path() +
                         QString::number(model_mesh_list[i].at(j)->Entity::id()) +
                         "   " +
                         QString::number(light_mesh_list[i].at(j)->id()));
        }
    }
    debugMessage("  need to update: " + QString::number(instances_to_load_list.size()));
}







//private
//add the light to the light list (contains also instances)
void LightLibrary::addLight(Light * light){
    if(!containsLight(light)){
        light_list.push_back(light);
        addLightData(light);
    }
}

//add the model to the unique model list (does not contain instances)
void LightLibrary::addLightUnique(Light * light){
    //do not check if there are instances, cause we know there is a base we instanced from!
    unique_light_list.push_back(light);
    unique_light_path_list.push_back(light->getModel()->get_path());
    instances_to_load_list.append(QList<Light*>());
}

void LightLibrary::addLightInstanceToLoad(Light * light){
    for(int i = 0; i < unique_light_path_list.size(); i++){
        //get the right index to sort it in
        if(unique_light_path_list.at(i).compare(light->getModel()->get_path()) == 0){
            instances_to_load_list[i].push_back(light);
            return;
        }
    }
    debugMessage("LightLibrary::addLightInstanceToLoad: could not sort in the instance: " +
                 light->getModel()->get_path());
}


//sort in the model data so we can skip several render setup calls...
void LightLibrary::addLightData(Light * light){
    QList<Mesh*> mdl_meshs = light->getModel()->get_meshs();

    QList<Mesh *>::iterator i;
    for (i = mdl_meshs.begin(); i != mdl_meshs.end(); ++i){
        Mesh * mesh = *i;
        //we have a mesh, let's check if we have it already sorted into our lists:
        Material* mesh_mtl = mesh->get_material();
        bool sort_in = false;
        int sort_in_index = -1;
        for(int j = 0; j < material_mesh_list.size(); j++){
            if(mesh_mtl->equal(*material_mesh_list.at(j))){
                //we have it already sorted in, just init the addition of the
                //resources to the existing lists
                sort_in_index = j;
                sort_in = true;
                break;
            }
        }
        if(sort_in){
            mesh_model_list[sort_in_index].append(mesh);
            model_mesh_list[sort_in_index].append(light->getModel());
            light_mesh_list[sort_in_index].append(light);
        }
        else{
            //model is not found in the lists, create a new entry
            material_mesh_list.append(mesh_mtl);
            mesh_model_list.append(QList<Mesh*>());
            model_mesh_list.append(QList<Model*>());
            light_mesh_list.append(QList<Light*>());
            int size_index = mesh_model_list.size()-1;
            mesh_model_list[size_index].append(mesh);
            model_mesh_list[size_index].append(light->getModel());
            light_mesh_list[size_index].append(light);
        }
    }
}

//we have to update newly loaded light's model
void LightLibrary::updateInstances(Model * mdl){
    for(int i = 0; i < unique_light_path_list.size(); i++){
        //get the right index to sort it in
        if(unique_light_path_list.at(i).compare(mdl->get_path()) == 0){
            //update all instances and sort them in correctly to render
            for(int j = 0; j < instances_to_load_list.at(i).size(); j++){
                Light * l = instances_to_load_list.at(i).at(j);
                l->getModel()->instance_from(*mdl);
                addLight(l);
            }
            instances_to_load_list[i].clear();
        }
    }
}

Light * LightLibrary::containsLightData(Light * light){
    QList<Light *>::iterator i;
    for (i = unique_light_list.begin(); i != unique_light_list.end(); ++i){
        Light * l = *i;
        if((*l).equalData(*light)){
            return l;
        }
    }
    return 0;
}

Light * LightLibrary::containsLight(Light * light){
    QList<Light *>::iterator i;
    for (i = light_list.begin(); i != light_list.end(); ++i){
        Light * l = *i;
        if(*l == *light){
            return l;
        }
    }
    return 0;
}

bool LightLibrary::removeLight(Light * light){
    QList<Light *>::iterator i;
    int j = 0;
    for (i = light_list.begin(); i != light_list.end(); ++i){
        Light * l = *i;
        if(*l == *light){
            light_list.removeAt(j);
            return true;
        }
        j++;
    }

    //model not even loaded yet!
    return false;
}



//EVENT LISTENER
//do not invoke the parents method...
void LightLibrary::eventRecieved(Event e){
    if(e.type == Event::EventModelStreamedFromDisk){
        //get the model and the light back together...
        Light *l;
        Model *m = e.streamer->getModel();
        int remove_index = -1;
        for(int i = 0; i < light_loading.size(); i++){
            if(*model_loading[i] == *m){
                //we found it... get the both together...
                l = light_loading[i];
                l->set_model_data(m);
                remove_index = i;
            }
        }
        if(remove_index>-1){
            model_loading.removeAt(remove_index);
            light_loading.removeAt(remove_index);
        }

        addLight(l);
        //check if some models actually got instanced during the time this model was loading...
        //and assign the new model data to them...
        updateInstances(m);
    }
}

//EVENT TRANSMITTER
void LightLibrary::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}
