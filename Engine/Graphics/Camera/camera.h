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
    void rotate_local_post(float angle, float axis_x, float axis_y, float axis_z);    // no gimbal lock
    void rotate_local_pre(float angle, float axis_x, float axis_y, float axis_z);     // along axis
    // global - world rotates
    void rotate_global_post(float angle, float axis_x, float axis_y, float axis_z);    // no gimbal lock
    void rotate_global_pre(float angle, float axis_x, float axis_y, float axis_z);     // along axis

    void move(float x_dir, float y_dir, float z_dir);
    void translate(float x_dir, float y_dir, float z_dir);




    Matrix4x4 M_camera_view;
    Matrix4x4 M_camera_rotation_local;
    Matrix4x4 M_camera_rotation_global;
    Matrix4x4 M_camera_rotation;
    Matrix4x4 M_camera_translation;
};

#endif // CAMERA_H
