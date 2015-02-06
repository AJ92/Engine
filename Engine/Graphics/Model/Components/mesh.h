#ifndef MESH_H
#define MESH_H


#include "Graphics/OpenGL/OpenGL.h"
#include "Graphics/Model/Components/material.h"
#include "Object/object.h"
#include "mathematics.h"

#include <QString>
#include <QStringList>

#include "Object/SmartPointer/smartpointer.h"

class Material;

class Mesh : public Object
{
public:
    Mesh(QString name,int triangle_count,GLfloat vertices[],GLfloat texcoords[],GLfloat normals[],
         SP<Material> material);
    virtual ~Mesh();

    QString get_name();

    SP<Material> get_material();
    void set_material(SP<Material> mtl);

    int get_triangle_count();

    GLfloat* get_vertices();
    GLfloat* get_texcoords();
    GLfloat* get_normals();

    GLuint get_vertex_vbo();
    GLuint get_texcoord_vbo();
    GLuint get_normal_vbo();

    GLuint get_vertex_array_object();

    void loadGLdata();

    bool isLoaded();

    void set_vertex(int index, float x, float y, float z);
    void set_vertex(int index, Vector3 vector);

    Vector3 get_vertex(int index);

    //bounding sphere getters and setters
    Vector3 getBoundingSpherePos();
    double getBoundingSphereRadius();

    void setBoundingSpherePos(Vector3 pos);
    void setBoundingSphereRadius(double radius);

private:

    QString mesh_name;
    SP<Material> material;

    int triangle_count;

    //pointer to float arrays
    GLfloat* vertices;
    GLfloat* texcoords;
    GLfloat* normals;

    //vertex buffer objects (vertices, texcoords and normals)
    GLuint vertex_vbo;
    GLuint texcoord_vbo;
    GLuint normal_vbo;

    GLuint vertex_array_object;

    bool loaded;

    //for frustum culling
    //the bounding sphere in model space
    Vector3 bounding_sphere_position;
    double bounding_sphere_radius;
};

#endif // MESH_H
