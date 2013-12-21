#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include <QtGui/qvector3d.h>
#include <QtGui/qvector2d.h>
#include <QtGui/qmatrix4x4.h>
#include <QString>
#include <QStringList>

#include <QMap>

#include "World/resources.h"
#include "Model/mesh.h"
#include "Model/material.h"

//load files
#include <qfile.h>
#include <qtextstream.h>

class Resources;
class Mesh;
class Material;

class Model
{
public:
    //MODEL
    Model(QString path, Resources* resources, bool &ok);
    //INSTANCE FROM MODEL
    Model(Model* model,bool &ok);
    //MODEL FROM DATA
    Model(QString name, QList<Mesh*> mesh_list, Resources* resources, bool &ok);

    ~Model();

    QMatrix4x4 m_rotation;
    QMatrix4x4 m_translation;
    QMatrix4x4 m_scale;
    //final matrix
    QMatrix4x4 m_modelview;

    void rotate         (float angle, float x_axis, float y_axis, float z_axis);
    void rotate_reset   ();
    void translate      (float x_pos, float y_pos,  float z_pos);
    void scale          (float x_sca, float y_sca,  float z_sca);

    void build_model_view();

    QVector3D get_view_dir();
    QVector3D get_pos();
    QVector3D get_scale();

    bool is_visible();
    void set_visible(bool visibility);

    Resources* get_resman();
    QString get_model_name();
    QList<Mesh*> get_meshs();

    bool is_instanced();
    bool is_instance_base();
    Model* create_instance();

    static long next_id();
    long get_id();

    Model* get_instance_base();

private:

    static long next_identifier;
    const long identifier;

    //position rotation scalation...
    float x;
    float y;
    float z;

    float x_scale;
    float y_scale;
    float z_scale;

    bool instance;
    bool instance_base;
    Model* instanced_from;

    int debug;

    //MODEL ATTRIBUTES:
    int visible;
    int lit;
    QVector3D light_color;
    float light_strength;
    int alpha_transparency;
    int black_transparency;
    float transparency;
    int sort;

    //MODEL DATA:
    QString model_name;

    //MODEL RESOURCE DATA:
    Resources* resman;
    QList<Mesh*> meshs;

    bool load_file_obj(QString path);
};

#endif // MODEL_H
