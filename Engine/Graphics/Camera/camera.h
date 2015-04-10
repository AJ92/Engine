#ifndef CAMERA_H
#define CAMERA_H

#include "Object/object.h"
#include "Object/component.h"
#include "mathematics.h"

class Camera : public Component
{
public:
    Camera();
    virtual ~Camera();

    // local - cam rotates
    void rotate_local_post_x(double angle);    // no gimbal lock
    void rotate_local_post_y(double angle);
    void rotate_local_post_z(double angle);

    void rotate_local_pre_x(double angle);     // along axis
    void rotate_local_pre_y(double angle);
    void rotate_local_pre_z(double angle);

    // global - world rotates
    void rotate_global_post_x(double angle);    // no gimbal lock
    void rotate_global_post_y(double angle);
    void rotate_global_post_z(double angle);

    void rotate_global_pre_x(double angle);     // along axis
    void rotate_global_pre_y(double angle);
    void rotate_global_pre_z(double angle);


    void move(double x_dir, double y_dir, double z_dir);
    void translate(double x_dir, double y_dir, double z_dir);


    Matrix4x4 get_view_matrix();
    Matrix4x4 get_rotation_local_matrix();

    Vector3 getPosition();
    void set_position(double x, double y, double z);
    void set_position(Vector3 position);

    //rotate at translate pos
    void set_rotation_local(double angle, double x, double y, double z);
    void set_rotation_local(double angle, Vector3 rotation);

    void clear_rotation_local();

    void add_rotation_local(double angle, double x, double y, double z);
    void add_rotation_local(double angle, Vector3 rotation);

    //rotate around translate pos
    void set_rotation_global(double angle, double x, double y, double z);
    void set_rotation_global(double angle, Vector3 rotation);

    void clear_rotation_global();

    void add_rotation_global(double angle, double x, double y, double z);
    void add_rotation_global(double angle, Vector3 rotation);

    double getFOV();
    double getZNEAR();
    double getZFAR();

    void setFOV(double fov);
    void setZNEAR(double znear);
    void setZFAR(double zfar);


    Vector3 getDirForward();
    Vector3 getDirUp();
    Vector3 getDirRight();




private:

    //frustum settings
    double Z_FAR;
    double Z_NEAR;
    double FOV;

    bool matrix_changed;

    //translation, scale, rotation...
    Vector3 pos;

    double angle_global;
    Vector3 rot_global;

    double angle_local;
    Vector3 rot_local;

    Vector3 scl;

    //final one
    Matrix4x4 M_camera_view;

    Matrix4x4 M_camera_rotation_local;
    Matrix4x4 M_camera_rotation_global;
    Matrix4x4 M_camera_rotation;
    Matrix4x4 M_camera_translation;

    void set_matrix_pos();
    void set_matrix_rot_local();
    void set_matrix_rot_global();
    void add_matrix_rot_local();
    void add_matrix_rot_global();
    void set_matrix_scl();

    void build_view_matrix();
};

#endif // CAMERA_H
