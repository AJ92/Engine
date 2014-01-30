#ifndef CAMERA_H
#define CAMERA_H

#include "Object/object.h"
#include "Math/mathematics.h"

class Camera : public Object
{
public:
    Camera();
    ~Camera();
    float x;
    float y;
    float z;
    float Z_FAR;
    float Z_NEAR;
    float FOV;

    // local - cam rotates
    void rotate_local_post_x(float angle);    // no gimbal lock
    void rotate_local_post_y(float angle);
    void rotate_local_post_z(float angle);

    void rotate_local_pre_x(float angle);     // along axis
    void rotate_local_pre_y(float angle);
    void rotate_local_pre_z(float angle);

    // global - world rotates
    void rotate_global_post_x(float angle);    // no gimbal lock
    void rotate_global_post_y(float angle);
    void rotate_global_post_z(float angle);

    void rotate_global_pre_x(float angle);     // along axis
    void rotate_global_pre_y(float angle);
    void rotate_global_pre_z(float angle);


    void move(float x_dir, float y_dir, float z_dir);
    void translate(float x_dir, float y_dir, float z_dir);




    Matrix4x4 M_camera_view;
    Matrix4x4 M_camera_rotation_local;
    Matrix4x4 M_camera_rotation_global;
    Matrix4x4 M_camera_rotation;
    Matrix4x4 M_camera_translation;
};

#endif // CAMERA_H
