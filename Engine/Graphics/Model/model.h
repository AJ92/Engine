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
    void instance_from(const Model &mdl);

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

    Matrix4x4 get_model_matrix();

    void set_path(QString path);
    QString get_path() const;

    void add_mesh(Mesh* mesh);

    QList<Mesh*> get_meshs();

    void loadGLdata();
    bool isReadyToRender();

    bool equalData(const Model &mdl) const;

    //override + overload bam
    bool equal(const Model &mdl) const;

    friend bool operator==(const Model &mdl1, const Model &mdl2);

private:
    bool isReady;

    bool matrix_changed;

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

    QString path;

    QList<Mesh*> meshs;
};

#endif // MODEL_H
