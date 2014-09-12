#include "positation.h"

#include "Event/event.h"

Positation::Positation() :
    EventTransmitter()
{
    pos = Vector3(0,0,0);
    angle = 0.0;
    rot = Vector3(0,0,0);
    scl = Vector3(1,1,1);
    size = 0.0;
    matrix_changed = true;
}

void Positation::set_data(const Positation &positation){
    this->pos = positation.pos;
    this->rot = positation.rot;
    this->scl = positation.scl;
    this->mat_pos = positation.mat_pos;
    this->mat_rot = positation.mat_rot;
    this->mat_scl = positation.mat_scl;
    this->mat_m = positation.mat_m;
    this->matrix_changed = positation.matrix_changed;
}

Vector3 Positation::getPosition(){
    return pos;
}

void Positation::set_position(double x, double y, double z){
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    set_matrix_pos();
}

void Positation::set_position(Vector3 position){
    pos = position;
    set_matrix_pos();
}


void Positation::set_rotation(double angle, double x, double y, double z){
    this->angle = angle;
    rot[0] = x;
    rot[1] = y;
    rot[2] = z;
    set_matrix_rot();
}

void Positation::set_rotation(double angle, Vector3 rotation){
    this->angle = angle;
    rot = rotation;
    set_matrix_rot();
}

void Positation::clear_rotation(){
    mat_rot.set_to_identity();
    matrix_changed = true;
}

void Positation::add_rotation(double angle, double x, double y, double z){
    mat_rot.rotate(angle, x, y, z);
    matrix_changed = true;
}

void Positation::add_rotation(double angle, Vector3 rotation){
    mat_rot.rotate(angle, rotation);
    matrix_changed = true;
}

void Positation::set_rotation_matrix(Matrix4x4 mat){
    mat_rot = mat;
    matrix_changed = true;
}

void Positation::set_scale(double x, double y, double z){
    scl[0] = x;
    scl[1] = y;
    scl[2] = z;
    set_matrix_scl();
}

void Positation::set_scale(Vector3 scale){
    scl = scale;
    set_matrix_scl();
}

Vector3 Positation::get_scale(){
    return scl;
}

double Positation::get_size(){
    return size;
}


Matrix4x4 Positation::get_model_matrix(){
    build_model_matrix();
    return mat_m;
}

void Positation::set_matrix_pos(){
    mat_pos.translate(pos);
    matrix_changed = true;
}

void Positation::set_matrix_rot(){
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

void Positation::set_matrix_scl(){
    mat_scl.scale(scl);
    matrix_changed = true;
}

void Positation::build_model_matrix(){
    if(matrix_changed){
        mat_m =  mat_pos * mat_rot * mat_scl;
        matrix_changed = false;
    }
}

void Positation::sendMovedEvent(){

}

void Positation::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}