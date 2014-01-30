#include "camera.h"

Camera::Camera() :
    Object()
{
    M_camera_view.set_to_identity();
    M_camera_rotation_local.set_to_identity();
    M_camera_rotation_global.set_to_identity();
    M_camera_rotation.set_to_identity();
    M_camera_translation.set_to_identity();
    Z_FAR = 1000.0f;
    Z_NEAR = 1.0;
    FOV = 45.0f;
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    M_camera_view = M_camera_translation * M_camera_rotation;
}


//LOCAL
void Camera::rotate_local_post_x(float angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_x(angle);
    M_camera_rotation_local =  M_camera_rotation_local * camerarotation;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}

void Camera::rotate_local_post_y(float angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_y(angle);
    M_camera_rotation_local =  M_camera_rotation_local * camerarotation;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}

void Camera::rotate_local_post_z(float angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_z(angle);
    M_camera_rotation_local =  M_camera_rotation_local * camerarotation;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}





void Camera::rotate_local_pre_x(float angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_x(angle);
    M_camera_rotation_local =  camerarotation * M_camera_rotation_local;
    //M_camera_rotation = M_camera_rotation_local;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}

void Camera::rotate_local_pre_y(float angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_y(angle);
    M_camera_rotation_local =  camerarotation * M_camera_rotation_local;
    //M_camera_rotation = M_camera_rotation_local;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}

void Camera::rotate_local_pre_z(float angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_z(angle);
    M_camera_rotation_local =  camerarotation * M_camera_rotation_local;
    //M_camera_rotation = M_camera_rotation_local;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}







//GLOBAL
void Camera::rotate_global_post_x(float angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_x(angle);
    M_camera_rotation_global =  M_camera_rotation_global * camerarotation;
    //M_camera_rotation = M_camera_rotation_global;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}

void Camera::rotate_global_post_y(float angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_y(angle);
    M_camera_rotation_global =  M_camera_rotation_global * camerarotation;
    //M_camera_rotation = M_camera_rotation_global;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}

void Camera::rotate_global_post_z(float angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_z(angle);
    M_camera_rotation_global =  M_camera_rotation_global * camerarotation;
    //M_camera_rotation = M_camera_rotation_global;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}







void Camera::rotate_global_pre_x(float angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_x(angle);
    M_camera_rotation_global =  camerarotation * M_camera_rotation_global;
    //M_camera_rotation = M_camera_rotation_global;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}

void Camera::rotate_global_pre_y(float angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_y(angle);
    M_camera_rotation_global =  camerarotation * M_camera_rotation_global;
    //M_camera_rotation = M_camera_rotation_global;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}

void Camera::rotate_global_pre_z(float angle)
{
    Matrix4x4 camerarotation;
    camerarotation.rotate_z(angle);
    M_camera_rotation_global =  camerarotation * M_camera_rotation_global;
    //M_camera_rotation = M_camera_rotation_global;
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;
}






void Camera::move(float x_dir, float y_dir, float z_dir)
{
    /*
                right     up    forward
                    0     1     2               3
                    4     5     6               7
                    8     9    10               11


                    12    13   14               15
        */


    x = x + (x_dir * M_camera_view[0]);        //right / left
    y = y + (x_dir * M_camera_view[4]);
    z = z + (x_dir * M_camera_view[8]);

    x = x + (y_dir * M_camera_view[1]);        //up / down
    y = y + (y_dir * M_camera_view[5]);
    z = z + (y_dir * M_camera_view[9]);

    x = x + (z_dir * M_camera_view[2]);        //forward / backward
    y = y + (z_dir * M_camera_view[6]);
    z = z + (z_dir * M_camera_view[10]);

    M_camera_translation.translate(x,y,z);
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;

}

void Camera::translate(float x_dir, float y_dir, float z_dir)
{

    M_camera_translation.set_to_identity();
    M_camera_translation.translate(x_dir,y_dir,z_dir);
    M_camera_view = M_camera_rotation_global * M_camera_translation * M_camera_rotation_local;

}


Camera::~Camera()
{
    //destructor
}
