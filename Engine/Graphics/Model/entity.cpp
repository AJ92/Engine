#include "entity.h"

Entity::Entity() :
    Object()
{
    pos = Vector3(0,0,0);
    angle = 0.0;
    rot = Vector3(0,0,0);
    scl = Vector3(1,1,1);
    size = 0.0;
    matrix_changed = true;
}

void Entity::set_data(const Entity &entity){
    this->pos = entity.pos;
    this->rot = entity.rot;
    this->scl = entity.scl;
    this->mat_pos = entity.mat_pos;
    this->mat_rot = entity.mat_rot;
    this->mat_scl = entity.mat_scl;
    this->mat_m = entity.mat_m;
    this->matrix_changed = entity.matrix_changed;
}

Vector3 Entity::getPosition(){
    return pos;
}

void Entity::set_position(double x, double y, double z){
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    set_matrix_pos();
}

void Entity::set_position(Vector3 position){
    pos = position;
    set_matrix_pos();
}


void Entity::set_rotation(double angle, double x, double y, double z){
    this->angle = angle;
    rot[0] = x;
    rot[1] = y;
    rot[2] = z;
    set_matrix_rot();
}

void Entity::set_rotation(double angle, Vector3 rotation){
    this->angle = angle;
    rot = rotation;
    set_matrix_rot();
}

void Entity::clear_rotation(){
    mat_rot.set_to_identity();
    matrix_changed = true;
}

void Entity::add_rotation(double angle, double x, double y, double z){
    mat_rot.rotate(angle, x, y, z);
    matrix_changed = true;
}

void Entity::add_rotation(double angle, Vector3 rotation){
    mat_rot.rotate(angle, rotation);
    matrix_changed = true;
}

void Entity::set_rotation_matrix(Matrix4x4 mat){
    mat_rot = mat;
    matrix_changed = true;
}

void Entity::set_scale(double x, double y, double z){
    scl[0] = x;
    scl[1] = y;
    scl[2] = z;
    set_matrix_scl();
}

void Entity::set_scale(Vector3 scale){
    scl = scale;
    set_matrix_scl();
}

Vector3 Entity::get_scale(){
    return scl;
}

double Entity::get_size(){
    return size;
}


Matrix4x4 Entity::get_model_matrix(){
    build_model_matrix();
    return mat_m;
}

void Entity::set_matrix_pos(){
    mat_pos.translate(pos);
    matrix_changed = true;
}

void Entity::set_matrix_rot(){
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

void Entity::set_matrix_scl(){
    mat_scl.scale(scl);
    matrix_changed = true;
}

void Entity::build_model_matrix(){
    if(matrix_changed){
        mat_m =  mat_pos * mat_rot * mat_scl;
        matrix_changed = false;
    }
}


