#include "modellibrary.h"

#include "Graphics/Model/model.h"
#include "Graphics/Model/Components/material.h"
#include "Graphics/Model/Components/mesh.h"

#include "Event/event.h"
#include "Object/compositeobject.h"

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
QList<Model *> ModelLibrary::getModels() const{
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

int ModelLibrary::modelCount(){
    return model_list.size();
}

void ModelLibrary::setModelsPerThread(int model_count){
    streamer->setModelsPerThread(model_count);
}


QList<QList<Mesh*> > ModelLibrary::getMeshModelList(){
    return mesh_model_list;
}

QList<QList<Model*> > ModelLibrary::getModelMeshList(){
    return model_mesh_list;
}

QList<Material*> ModelLibrary::getMaterialMeshList(){
    return material_mesh_list;
}


void ModelLibrary::debugModelData(){
    debugMessage("ModelLibrary Debug:");
    for(int i = 0; i < material_mesh_list.size(); i++){
        debugMessage("Mtl: " + material_mesh_list[i]->get_name() +
                     QString::number(material_mesh_list[i]->id()));
        for(int j = 0; j < mesh_model_list[i].size(); j++){
            debugMessage(" - Mesh: " + mesh_model_list[i].at(j)->get_name() +
                         QString::number(mesh_model_list[i].at(j)->id()) +
                         "   " + model_mesh_list[i].at(j)->get_path() +
                         QString::number(model_mesh_list[i].at(j)->id()));
        }
    }
}



//private
//add the model to the model list (contains also instances)
void ModelLibrary::addModel(Model * mdl){
    if(!containsModel(mdl)){
        model_list.push_back(mdl);
        addModelData(mdl);
    }
}

//add the model to the unique model list (does not contain instances)
void ModelLibrary::addModelUnique(Model * mdl){
    //do not check if there are instances, cause we know there is a base we instanced from!
    unique_model_list.push_back(mdl);
    unique_model_path_list.push_back(mdl->get_path());
    instances_to_load_list.append(QList<Model*>());
}

void ModelLibrary::addModelInstanceToLoad(Model * mdl){
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


//sort in the model data so we can skip several render setup calls...
void ModelLibrary::addModelData(Model * mdl){
    QList<Mesh*> mdl_meshs = mdl->get_meshs();

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
            model_mesh_list[sort_in_index].append(mdl);
        }
        else{
            //model is not found in the lists, create a new entry
            material_mesh_list.append(mesh_mtl);
            mesh_model_list.append(QList<Mesh*>());
            model_mesh_list.append(QList<Model*>());
            int size_index = mesh_model_list.size()-1;
            mesh_model_list[size_index].append(mesh);
            model_mesh_list[size_index].append(mdl);
        }
    }
}

void ModelLibrary::updateInstances(Model * mdl){
    for(int i = 0; i < unique_model_path_list.size(); i++){
        //get the right index to sort it in
        if(unique_model_path_list.at(i).compare(mdl->get_path()) == 0){
            //update all instances and sort them in correctly to render
            for(int j = 0; j < instances_to_load_list.at(i).size(); j++){
                Model * m = instances_to_load_list.at(i).at(j);
                m->instance_from(*mdl);
                addModel(m);
            }
            instances_to_load_list[i].clear();
        }
    }
}

Model * ModelLibrary::containsModelData(Model * mdl){
    QList<Model *>::iterator i;
    for (i = unique_model_list.begin(); i != unique_model_list.end(); ++i){
        Model * m = *i;
        if((*m).equalData(*mdl)){
            return m;
        }
    }
    return 0;
}

Model * ModelLibrary::containsModel(Model * mdl){
    QList<Model *>::iterator i;
    for (i = model_list.begin(); i != model_list.end(); ++i){
        Model * m = *i;
        if(*m == *mdl){
            return m;
        }
    }
    return 0;
}

bool ModelLibrary::removeModel(Model * mdl){
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
void ModelLibrary::eventRecieved(Event e){
    if(e.type == Event::EventModelStreamedFromDisk){
        addModel(e.streamer->getModel());
        //check if some models actually got instanced during the time this model was loading...
        //and assign the new model data to them...
        updateInstances(e.streamer->getModel());
    }
}

//EVENT TRANSMITTER
void ModelLibrary::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}













/////////////////////////
//
//        V2
//
/////////////////////////














ModelLibrary_v2::ModelLibrary_v2() :
    EventListener(),
    EventTransmitter()
{
    reserve_unique = 50;
    reserve_all = 200;
}

ModelLibrary_v2::ModelLibrary_v2(int reserve_unique, int reserve_all) :
    EventListener(),
    EventTransmitter()
{
    this->reserve_unique = reserve_unique;
    this->reserve_all = reserve_all;
}

void ModelLibrary_v2::initialize(){
    debugMessage("modellibrary v2 initializing...");

    //preallocate some memory  
    compositeobject_list.reserve(reserve_all);
    model_list.reserve(reserve_all);

    debugMessage("modellibrary v2 initialized.");
}

QList<Model *> ModelLibrary_v2::getModels() const{
    return model_list;
}

QList<CompositeObject*> ModelLibrary_v2::getCompositeObjects() const{
    return compositeobject_list;
}


int ModelLibrary_v2::modelCount(){
    return model_list.size();
}



QList<QList<CompositeObject*> > ModelLibrary_v2::getCompositeobjectMeshList(){
    return compositeobject_mesh_list;
}

QList<QList<Mesh*> > ModelLibrary_v2::getMeshModelList(){
    return mesh_model_list;
}

QList<QList<Model*> > ModelLibrary_v2::getModelMeshList(){
    return model_mesh_list;
}

QList<Material*> ModelLibrary_v2::getMaterialMeshList(){
    return material_mesh_list;
}


void ModelLibrary_v2::debugModelData(){
    debugMessage("ModelLibrary Debug:");
    for(int i = 0; i < material_mesh_list.size(); i++){
        debugMessage("Mtl: " + material_mesh_list[i]->get_name() +
                     QString::number(material_mesh_list[i]->id()));
        for(int j = 0; j < mesh_model_list[i].size(); j++){
            debugMessage(" - Mesh: " + mesh_model_list[i].at(j)->get_name() +
                         QString::number(mesh_model_list[i].at(j)->id()) +
                         "   " + model_mesh_list[i].at(j)->get_path() +
                         QString::number(model_mesh_list[i].at(j)->id()));
        }
    }
}

void ModelLibrary_v2::clearLib(){
    compositeobject_list.clear();       //all compositeobjects (includes model instances)
    model_list.clear();               //all models (includes instances)


    //model data sorted by material / single mesh
    compositeobject_mesh_list.clear();
    mesh_model_list.clear();
    model_mesh_list.clear();
    material_mesh_list.clear();
}

//private
//add the model to the model list (contains also instances)
void ModelLibrary_v2::addModel(CompositeObject * co){
    //check if CompositeObject was build properly...
    if(co->hasModel()){
        //check if it was added already...
        if(!containsCompositeObject(co)){
            addModelData(co);
        }
    }
    else{
        debugMessage("ModelLibrary_v2::addModel(CompositeObject * mdl): mdl has no Model* !!!");
    }
}





//sort in the model data so we can skip several render setup calls...
void ModelLibrary_v2::addModelData(CompositeObject * co){

    Model* mdl = co->getModel();

    //add it to the lists...

    model_list.push_back(mdl);
    compositeobject_list.push_back(co);




    QList<Mesh*> mdl_meshs = mdl->get_meshs();

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
            model_mesh_list[sort_in_index].append(mdl);
            compositeobject_mesh_list[sort_in_index].append(co);
        }
        else{
            //model is not found in the lists, create a new entry
            material_mesh_list.append(mesh_mtl);
            mesh_model_list.append(QList<Mesh*>());
            model_mesh_list.append(QList<Model*>());
            compositeobject_mesh_list.append(QList<CompositeObject*>());
            int size_index = mesh_model_list.size()-1;
            mesh_model_list[size_index].append(mesh);
            model_mesh_list[size_index].append(mdl);
            compositeobject_mesh_list[size_index].append(co);
        }
    }
}



Model * ModelLibrary_v2::containsModelData(Model * mdl){
    QList<Model *>::iterator i;
    for (i = model_list.begin(); i != model_list.end(); ++i){
        Model * m = *i;
        if((*m).equalData(*mdl)){
            return m;
        }
    }
    return 0;
}

Model * ModelLibrary_v2::containsModel(Model * mdl){
    QList<Model *>::iterator i;
    for (i = model_list.begin(); i != model_list.end(); ++i){
        Model * m = *i;
        if(*m == *mdl){
            return m;
        }
    }
    return 0;
}

CompositeObject * ModelLibrary_v2::containsCompositeObject(CompositeObject * co){
    QList<CompositeObject *>::iterator i;
    for (i = compositeobject_list.begin(); i != compositeobject_list.end(); ++i){
        CompositeObject * c = *i;
        //if(*c == *co){
        if(c->EventListener::id() == co->EventListener::id() ){
            return c;
        }
    }
    return 0;
}

//untested crappy delete function ...
//guessed O(over 9000)
bool ModelLibrary_v2::removeModel(CompositeObject * co){

    //delete from the simple list...
    QList<CompositeObject *>::iterator i;
    int j = 0;
    for (i = compositeobject_list.begin(); i != compositeobject_list.end(); ++i){
        CompositeObject * c = *i;
        //if(*c == *co){
        if(c->EventListener::id() == co->EventListener::id() ){
            model_list.removeAt(j);
            compositeobject_list.removeAt(j);
            break;
        }
        j++;
    }

    QList<int>          index_i;
    QList<QList<int> >  index_i_k;


    //delete the model from the data lists...
    for(int i = 0; i < compositeobject_mesh_list.size(); i++){
        bool created = false;
        for(int k = 0; k < compositeobject_mesh_list.at(i).size(); k++){
            //if(*compositeobject_mesh_list.at(i).at(k) == *co){
            if(compositeobject_mesh_list.at(i).at(k)->EventListener::id() == co->EventListener::id()){
                if(!created){
                    index_i.append(i);
                    index_i_k.append(QList<int>());
                    created = true;
                }
                index_i_k[index_i_k.size()-1].append(k);
            }
        }
    }

    for(int i = 0; i < index_i.size(); i++){
        for(int k = 0; k < index_i_k.size(); k++){
            compositeobject_mesh_list[index_i.at(i)].removeAt(index_i_k.at(i).at(k));
            mesh_model_list[index_i.at(i)].removeAt(index_i_k.at(i).at(k));
            model_mesh_list[index_i.at(i)].removeAt(index_i_k.at(i).at(k));
        }
    }
    return true;
}



//EVENT LISTENER
//do not invoke the parents method...
void ModelLibrary_v2::eventRecieved(Event e){
    /*
    if(e.type == Event::EventModelStreamedFromDisk){

    }
    */
}

//EVENT TRANSMITTER
void ModelLibrary_v2::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}
