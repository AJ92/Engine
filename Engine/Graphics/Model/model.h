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
    //create a copy from mdl...
    Model(const Model & mdl);
    //construct empty Model
    Model();

    void set_data(const Model &mdl);

    void set_position(float x, float y, float z);
    void set_position(Vector3 position);

    void set_rotation(float x, float y, float z);
    void set_rotation(Vector3 rotation);

    void set_scale(float x, float y, float z);
    void set_scale(Vector3 scale);

    Matrix4x4 get_model_matrix();

    void set_path(QString path);
    QString get_path() const;

    void add_mesh(Mesh* mesh);

    QList<Mesh*> get_meshs();

    void loadGLdata();
    bool isReadyToRender();

    //override + overload bam
    bool equal(const Model &mdl) const;

    friend bool operator==(const Model &mdl1, const Model &mdl2);

private:
    bool isReady;

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

    QString path;

    QList<Mesh*> meshs;
};

#endif // MODEL_H
