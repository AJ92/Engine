#include "model.h"

#include "Graphics/Model/Components/material.h"
#include "Graphics/Model/Components/mesh.h"


Model::Model(const Model &mdl) :
    Entity()
{
    //copy all the stuff to this new object
    //lets hope const keyword won't make trouble
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
    this->isReady = mdl.isReady;
}

Model::Model() :
    Entity()
{
    isReady = false;
}

void Model::instance_from(const Model &mdl){
    this->meshs = mdl.meshs;
    this->isReady = mdl.isReady;
}


void Model::set_data(const Model &mdl){
    this->pos = mdl.pos;
    this->rot = mdl.rot;
    this->scl = mdl.scl;
    this->mat_pos = mdl.mat_pos;
    this->mat_rot = mdl.mat_rot;
    this->mat_scl = mdl.mat_scl;
    this->mat_m = mdl.mat_m;
    this->matrix_changed = mdl.matrix_changed;
    this->isReady = mdl.isReady;
}

void Model::set_path(QString path){
    this->path = path;
}

QString Model::get_path() const{
    return path;
}

void Model::add_mesh(Mesh* mesh){
    meshs.append(mesh);
}

QList<Mesh*> Model::get_meshs(){
    return meshs;
}

void Model::loadGLdata(){
    for(int i = 0; i < meshs.size(); i++){
        Mesh * mesh = meshs.at(i);
        Material * mtl = mesh->get_material();

        if(!mtl->isLoaded()){
            mtl->loadGLdata();
        }
        if(!mesh->isLoaded()){
            mesh->loadGLdata();
        }
    }
    isReady = true;
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




