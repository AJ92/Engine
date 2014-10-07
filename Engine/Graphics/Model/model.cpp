#include "model.h"

#include "Graphics/Model/Components/material.h"
#include "Graphics/Model/Components/mesh.h"
#include "Event/event.h"

#include "Object/compositeobject.h"


Model::Model(const Model &mdl) :
    EventTransmitter()
{
    //copy all the stuff to this new object
    //lets hope const keyword won't make trouble
    /*
    this->pos = mdl.pos;
    this->rot = mdl.rot;
    this->scl = mdl.scl;
    this->mat_pos = mdl.mat_pos;
    this->mat_rot = mdl.mat_rot;
    this->mat_scl = mdl.mat_scl;
    this->mat_m = mdl.mat_m;
    this->matrix_changed = mdl.matrix_changed;
    this->path = mdl.path;
    this->meshs = mdl.meshs;
    this->size = 0.0;
    */
    this->parent_co = mdl.parent_co;
    this->path = mdl.path;
    this->isReady = mdl.isReady;
    this->parent_co = mdl.parent_co;
    this->size = 0.0;
}

Model::Model() :
    EventTransmitter()
{
    isReady = false;
    parent_co = 0;
    size = 0.0;
}

Model::~Model(){
    qDebug("Model::~Model");
}

double Model::get_size(){
    return size;
}

double Model::max(double a, double b){
    if(a > b){
        return a;
    }
    return b;
}

void Model::recalculate_size(){
    double temp_size = this->size;
    for(int i = 0; i < meshs.size(); i++){
        Vector3 pos = meshs[i]->getBoundingSpherePos();
        double rad = meshs[i]->getBoundingSphereRadius();
        temp_size = max(pos.length() + rad, temp_size);
    }
    this->size = temp_size;
}

void Model::instance_from(const Model &mdl){
    this->meshs = mdl.meshs;
    this->isReady = mdl.isReady;
    recalculate_size();
}


void Model::set_data(const Model &mdl){
    /*
    this->pos = mdl.pos;
    this->rot = mdl.rot;
    this->scl = mdl.scl;
    this->mat_pos = mdl.mat_pos;
    this->mat_rot = mdl.mat_rot;
    this->mat_scl = mdl.mat_scl;
    this->mat_m = mdl.mat_m;
    this->matrix_changed = mdl.matrix_changed;
    */

    this->setListeners(mdl.getAllListeners());

    //this->parent_co = parent_co;
    //this->isReady = mdl.isReady;
}

void Model::set_path(QString path){
    this->path = path;
}

QString Model::get_path() const{
    return path;
}

void Model::add_mesh(SP<Mesh> mesh){
    meshs.append(mesh);
    recalculate_size();
}

QList<SP<Mesh> > Model::get_meshs(){
    return meshs;
}

void Model::loadGLdata(){
    for(int i = 0; i < meshs.size(); i++){
        SP<Mesh> mesh = meshs.at(i);
        SP<Material> mtl = mesh->get_material();

        if(!mtl->isLoaded()){
            mtl->loadGLdata();
        }
        if(!mesh->isLoaded()){
            mesh->loadGLdata();
        }
    }
    isReady = true;
    qDebug("Model::loadGLdata()");
}

bool Model::isReadyToRender(){
    return isReady;
}

bool Model::equalData(const Model &mdl) const{
    if(this->path.compare(mdl.get_path())==0){
        return true;
    }
    return false;
}


void Model::setParentCompositeObject(SP<CompositeObject> co){
    this->parent_co = co;
}

SP<CompositeObject> Model::getParentCompositeObject(){
    return parent_co;
}


bool Model::equal(const Model &mdl) const{
    if(this->path.compare(mdl.get_path())==0 && this->id() == mdl.id()){
        return true;
    }
    return false;
}

//friend
bool operator==(const Model &mdl1, const Model &mdl2){
    return mdl1.equal(mdl2);
}


