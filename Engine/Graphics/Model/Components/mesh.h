#ifndef MESH_H
#define MESH_H


#include "Graphics/OpenGL/OpenGL.h"
#include "Graphics/Model/Components/material.h"
#include "Object/object.h"
#include "Math/Vector/vector3.h"

#include <QString>
#include <QStringList>

class Material;

class Mesh : public Object
{
public:
    Mesh(QString name,int triangle_count,GLfloat vertices[],GLfloat texcoords[],GLfloat normals[],
         GLuint vertex_vbo, GLuint texcoord_vbo, GLuint normal_vbo, Material *material);
    ~Mesh();

    QString get_name();

    Material* get_material();
    void set_material(Material *mtl);

    int get_triangle_count();

    GLfloat* get_vertices();
    GLfloat* get_texcoords();
    GLfloat* get_normals();

    GLuint get_vertex_vbo();
    GLuint get_texcoord_vbo();
    GLuint get_normal_vbo();

    void set_vertex(int index, float x, float y, float z);
    void set_vertex(int index, Vector3 vector);

    Vector3 get_vertex(int index);

private:

    QString mesh_name;
    Material* material;

    int triangle_count;

    //pointer to float arrays
    GLfloat* vertices;
    GLfloat* texcoords;
    GLfloat* normals;

    //vertex buffer objects (vertices, texcoords and normals)
    GLuint vertex_vbo;
    GLuint texcoord_vbo;
    GLuint normal_vbo;
};

#endif // MESH_H
