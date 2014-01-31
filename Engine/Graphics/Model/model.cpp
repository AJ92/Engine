#include "model.h"


Model::Model(const Model &mdl) :
    Object()
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
    this->isReady = mdl.isReady;
}

Model::Model() :
    Object()
{
    pos = Vector3(0,0,0);
    rot = Vector3(0,0,0);
    scl = Vector3(1,1,1);
    matrix_changed = true;
    isReady = false;
}


void Model::set_position(float x, float y, float z){
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    set_matrix_pos();
}

void Model::set_position(Vector3 position){
    pos = position;
    set_matrix_pos();
}


void Model::set_rotation(float x, float y, float z){
    rot[0] = x;
    rot[1] = y;
    rot[2] = z;
    set_matrix_rot();
}

void Model::set_rotation(Vector3 rotation){
    pos = rotation;
    set_matrix_rot();
}


void Model::set_scale(float x, float y, float z){
    scl[0] = x;
    scl[1] = y;
    scl[2] = z;
    set_matrix_scl();
}

void Model::set_scale(Vector3 scale){
    scl = scale;
    set_matrix_scl();
}

Matrix4x4 Model::get_model_matrix(){
    build_model_matrix();
    return mat_m;
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
        mtl->loadGLdata();
        mesh->loadGLdata();
    }
    isReady = true;
}

bool Model::isReadyToRender(){
    return isReady;
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


void Model::set_matrix_pos(){
    mat_pos.translate(pos);
    matrix_changed = true;
}

void Model::set_matrix_rot(){
    mat_rot.rotate_x(rot.x());
    mat_rot.rotate_y(rot.y());
    mat_rot.rotate_z(rot.z());
    matrix_changed = true;
}

void Model::set_matrix_scl(){
    mat_scl.scale(scl);
    matrix_changed = true;
}

void Model::build_model_matrix(){
    if(matrix_changed){
        mat_m = mat_scl * mat_pos * mat_rot;
        matrix_changed = false;
    }
}


