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
    angle = 0.0;
    rot = Vector3(0,0,0);
    scl = Vector3(1,1,1);
    matrix_changed = true;
    isReady = false;
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

void Model::instance_from(const Model &mdl){
    this->meshs = mdl.meshs;
    this->isReady = mdl.isReady;
}

Vector3 Model::getPosition(){
    return pos;
}

void Model::set_position(double x, double y, double z){
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    set_matrix_pos();
}

void Model::set_position(Vector3 position){
    pos = position;
    set_matrix_pos();
}


void Model::set_rotation(double angle, double x, double y, double z){
    this->angle = angle;
    rot[0] = x;
    rot[1] = y;
    rot[2] = z;
    set_matrix_rot();
}

void Model::set_rotation(double angle, Vector3 rotation){
    this->angle = angle;
    rot = rotation;
    set_matrix_rot();
}

void Model::clear_rotation(){
    mat_rot.set_to_identity();
    matrix_changed = true;
}

void Model::add_rotation(double angle, double x, double y, double z){
    mat_rot.rotate(angle, x, y, z);
    matrix_changed = true;
}

void Model::add_rotation(double angle, Vector3 rotation){
    mat_rot.rotate(angle, rotation);
    matrix_changed = true;
}

void Model::set_rotation_matrix(Matrix4x4 mat){
    mat_rot = mat;
    matrix_changed = true;
}

void Model::set_scale(double x, double y, double z){
    scl[0] = x;
    scl[1] = y;
    scl[2] = z;
    set_matrix_scl();
}

void Model::set_scale(Vector3 scale){
    scl = scale;
    set_matrix_scl();
}

Vector3 Model::get_scale(){
    return scl;
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


void Model::set_matrix_pos(){
    mat_pos.translate(pos);
    matrix_changed = true;
}

void Model::set_matrix_rot(){
    /*
    Matrix4x4 rot_x;
    Matrix4x4 rot_y;
    Matrix4x4 rot_z;
    rot_x.rotate_x(rot[0]);
    rot_y.rotate_y(rot[1]);
    rot_z.rotate_z(rot[2]);
    mat_rot = rot_x * rot_y * rot_z;
    */
    Matrix4x4 rotation;
    rotation.rotate(angle,rot);
    mat_rot = rotation;
    matrix_changed = true;
}

void Model::set_matrix_scl(){
    mat_scl.scale(scl);
    matrix_changed = true;
}

void Model::build_model_matrix(){
    if(matrix_changed){
        mat_m =  mat_pos * mat_rot * mat_scl;
        matrix_changed = false;
    }
}


