#include "camera.h"

Camera::Camera() :
    Component()
{
    M_camera_view.set_to_identity();
    M_camera_rotation_local.set_to_identity();
    M_camera_rotation_global.set_to_identity();
    M_camera_rotation.set_to_identity();
    M_camera_translation.set_to_identity();
    Z_FAR = 1000.0;
    Z_NEAR = 1.0;
    FOV = 45.0;
    pos = Vector3(0,0,0);
    angle_local = 0.0;
    angle_global = 0.0;
    rot_local = Vector3(0,0,0);
    rot_global = Vector3(0,0,0);
    scl = Vector3(1,1,1);
    matrix_changed = true;
}


//LOCAL
void Camera::rotate_local_post_x(double angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_x(angle);
    M_camera_rotation_local =  M_camera_rotation_local * camerarotation;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}

void Camera::rotate_local_post_y(double angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_y(angle);
    M_camera_rotation_local =  M_camera_rotation_local * camerarotation;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}

void Camera::rotate_local_post_z(double angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_z(angle);
    M_camera_rotation_local =  M_camera_rotation_local * camerarotation;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}





void Camera::rotate_local_pre_x(double angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_x(angle);
    M_camera_rotation_local =  camerarotation * M_camera_rotation_local;
    //M_camera_rotation = M_camera_rotation_local;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}

void Camera::rotate_local_pre_y(double angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_y(angle);
    M_camera_rotation_local =  camerarotation * M_camera_rotation_local;
    //M_camera_rotation = M_camera_rotation_local;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}

void Camera::rotate_local_pre_z(double angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_z(angle);
    M_camera_rotation_local =  camerarotation * M_camera_rotation_local;
    //M_camera_rotation = M_camera_rotation_local;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}







//GLOBAL
void Camera::rotate_global_post_x(double angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_x(angle);
    M_camera_rotation_global =  M_camera_rotation_global * camerarotation;
    //M_camera_rotation = M_camera_rotation_global;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}

void Camera::rotate_global_post_y(double angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_y(angle);
    M_camera_rotation_global =  M_camera_rotation_global * camerarotation;
    //M_camera_rotation = M_camera_rotation_global;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}

void Camera::rotate_global_post_z(double angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_z(angle);
    M_camera_rotation_global =  M_camera_rotation_global * camerarotation;
    //M_camera_rotation = M_camera_rotation_global;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}







void Camera::rotate_global_pre_x(double angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_x(angle);
    M_camera_rotation_global =  camerarotation * M_camera_rotation_global;
    //M_camera_rotation = M_camera_rotation_global;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}

void Camera::rotate_global_pre_y(double angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_y(angle);
    M_camera_rotation_global =  camerarotation * M_camera_rotation_global;
    //M_camera_rotation = M_camera_rotation_global;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}

void Camera::rotate_global_pre_z(double angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_z(angle);
    M_camera_rotation_global =  camerarotation * M_camera_rotation_global;
    //M_camera_rotation = M_camera_rotation_global;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}






void Camera::move(double x_dir, double y_dir, double z_dir)
{
    /*
                right     up    forward
                    0     1     2               3
                    4     5     6               7
                    8     9    10               11


                    12    13   14               15
        */


    /*
    pos[0]  = pos[0] + (x_dir * M_camera_view[0]);        //right / left
    pos[1]  = pos[1]  + (x_dir * M_camera_view[4]);
    pos[2]  = pos[2]  + (x_dir * M_camera_view[8]);

    pos[0]  = pos[0]  + (y_dir * M_camera_view[1]);        //up / down
    pos[1]  = pos[1]  + (y_dir * M_camera_view[5]);
    pos[2]  = pos[2]  + (y_dir * M_camera_view[9]);

    pos[0]  = pos[0]  + (z_dir * M_camera_view[2]);        //forward / backward
    pos[1]  = pos[1]  + (z_dir * M_camera_view[6]);
    pos[2]  = pos[2]  + (z_dir * M_camera_view[10]);

    M_camera_translation.translate(pos[0] ,pos[1] ,pos[2] );
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
    */

}

void Camera::translate(double x_dir, double y_dir, double z_dir)
{
    /*
    x = x_dir;
    y = y_dir;
    z = z_dir;

    M_camera_translation.set_to_identity();
    M_camera_translation.translate(x_dir,y_dir,z_dir);
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
    */
}


void Camera::set_position(double x, double y, double z){
    pos[0] = -x;
    pos[1] = -y;
    pos[2] = -z;
    set_matrix_pos();
}

void Camera::set_position(Vector3 position){
    pos = -position;
    set_matrix_pos();
}


void Camera::set_rotation_local(double angle, double x, double y, double z){
    this->angle_local = angle;
    rot_local[0] = x;
    rot_local[1] = y;
    rot_local[2] = z;
    set_matrix_rot_local();
}

void Camera::set_rotation_local(double angle, Vector3 rotation){
    this->angle_local = angle;
    rot_local = rotation;
    set_matrix_rot_local();
}

void Camera::clear_rotation_local(){
    M_camera_rotation_local.set_to_identity();
    matrix_changed = true;
}

void Camera::add_rotation_local(double angle, double x, double y, double z){
    Matrix4x4 temp_rot;
    temp_rot.rotate(-angle, x, y, z);
    //pre multiply
    M_camera_rotation_local = temp_rot * M_camera_rotation_local;
    matrix_changed = true;
}

void Camera::add_rotation_local(double angle, Vector3 rotation){
    add_rotation_local(angle, rotation[0], rotation[1], rotation[2]);
}




void Camera::set_rotation_global(double angle, double x, double y, double z){
    this->angle_global = angle;
    rot_global[0] = x;
    rot_global[1] = y;
    rot_global[2] = z;
    set_matrix_rot_global();
}

void Camera::set_rotation_global(double angle, Vector3 rotation){
    this->angle_global = angle;
    rot_global = rotation;
    set_matrix_rot_global();
}

void Camera::clear_rotation_global(){
    M_camera_rotation_local.set_to_identity();
    matrix_changed = true;
}

void Camera::add_rotation_global(double angle, double x, double y, double z){
    M_camera_rotation_global.rotate(angle, x, y, z);
    matrix_changed = true;
}

void Camera::add_rotation_global(double angle, Vector3 rotation){
    M_camera_rotation_global.rotate(angle, rotation);
    matrix_changed = true;
}


/*
void Camera::set_scale(double x, double y, double z){
    scl[0] = x;
    scl[1] = y;
    scl[2] = z;
    set_matrix_scl();
}

void Camera::set_scale(Vector3 scale){
    scl = scale;
    set_matrix_scl();
}
*/

Matrix4x4 Camera::get_view_matrix(){
    build_view_matrix();
    return M_camera_view;
}

Matrix4x4 Camera::get_rotation_local_matrix(){
    return M_camera_rotation_local;
}

Vector3 Camera::getPosition(){
    return -pos;
}

double Camera::getFOV(){
    return FOV;
}

double Camera::getZNEAR(){
    return Z_NEAR;
}

double Camera::getZFAR(){
    return Z_FAR;
}

void Camera::setFOV(double fov){
    this->FOV = fov;
}

void Camera::setZNEAR(double znear){
    if(znear < 0.0001){
        this->Z_NEAR = 0.0001;
        return;
    }
    this->Z_NEAR = znear;
}

void Camera::setZFAR(double zfar){
    this->Z_FAR = zfar;
}


Vector3 Camera::getDirForward(){
    return Vector3(M_camera_view[2],M_camera_view[6], M_camera_view[10]);
}

Vector3 Camera::getDirUp(){
    return Vector3(M_camera_view[1],M_camera_view[5], M_camera_view[9]);
}

Vector3 Camera::getDirRight(){
    return Vector3(M_camera_view[0],M_camera_view[4], M_camera_view[8]);
}

void Camera::set_matrix_pos(){
    M_camera_translation.translate(pos);
    matrix_changed = true;
}

void Camera::set_matrix_rot_global(){
    Matrix4x4 rotation;
    rotation.rotate(angle_global,rot_global);
    M_camera_rotation_global = rotation;
    matrix_changed = true;
}

void Camera::set_matrix_rot_local(){
    Matrix4x4 rotation;
    rotation.rotate(angle_local,rot_local);
    M_camera_rotation_local = rotation;
    matrix_changed = true;
}

void Camera::add_matrix_rot_global(){

}

void Camera::add_matrix_rot_local(){

}

void Camera::set_matrix_scl(){
//not used, we don't scale the camera ...
}

void Camera::build_view_matrix(){
    if(matrix_changed){
        M_camera_view = M_camera_rotation_local * M_camera_translation * M_camera_rotation_global;
        matrix_changed = false;
    }
}


Camera::~Camera()
{
    //destructor
}
