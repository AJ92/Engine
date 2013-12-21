#ifndef MODEL_H
#define MODEL_H

#include "Object/object.h"
#include "Math/mathematics.h"

#include "Graphics/Model/Components/material.h"
#include "Graphics/Model/Components/mesh.h"

#include <QList>

class Mesh;

class Model : public Object
{
public:
    Model();

    void set_position(float x, float y, float z);
    void set_position(Vector3 position);

    void set_rotation(float x, float y, float z);
    void set_rotation(Vector3 rotation);

    void set_scale(float x, float y, float z);
    void set_scale(Vector3 scale);

    Matrix4x4 get_model_matrix();

    void add_mesh(Mesh* mesh);

private:
    bool matrix_changed;

    //translation, scale, rotation...
    Vector3 pos;
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

    QList<Mesh*> meshs;
};

#endif // MODEL_H
