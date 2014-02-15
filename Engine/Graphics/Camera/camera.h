#ifndef CAMERA_H
#define CAMERA_H

#include "Object/object.h"
#include "Math/mathematics.h"

class Camera : public Object
{
public:
    Camera();
    ~Camera();
    double x;
    double y;
    double z;
    double Z_FAR;
    double Z_NEAR;
    double FOV;

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




    Matrix4x4 M_camera_view;
    Matrix4x4 M_camera_rotation_local;
    Matrix4x4 M_camera_rotation_global;
    Matrix4x4 M_camera_rotation;
    Matrix4x4 M_camera_translation;
};

#endif // CAMERA_H
