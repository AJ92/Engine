#ifndef ENTITY_H
#define ENTITY_H

#include "Object/object.h"
#include "Math/mathematics.h"

class Entity : public Object
{
public:
    Entity();

    void set_data(const Entity &entity);

    Vector3 getPosition();
    void set_position(double x, double y, double z);
    void set_position(Vector3 position);

    void set_rotation(double angle, double x, double y, double z);
    void set_rotation(double angle, Vector3 rotation);

    void clear_rotation();
    void add_rotation(double angle, double x, double y, double z);
    void add_rotation(double angle, Vector3 rotation);

    void set_rotation_matrix(Matrix4x4 mat);

    void set_scale(double x, double y, double z);
    void set_scale(Vector3 scale);

    Vector3 get_scale();

    double get_size();

    Matrix4x4 get_model_matrix();

protected:

    bool matrix_changed;

    //spherical bound...
    double size;

    //translation, scale, rotation...
    Vector3 pos;
    double angle;
    Vector3 rot;
    Vector3 scl;

    Matrix4x4 mat_pos;
    Matrix4x4 mat_rot;
    Matrix4x4 mat_scl;

    Matrix4x4 mat_m;

    void set_matrix_pos();
    void set_matrix_rot();
    void set_matrix_scl();

    void build_model_matrix();
};

#endif // ENTITY_H
