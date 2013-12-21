#ifndef MESH_H
#define MESH_H

#include "material.h"
#include <QVector>
#include <QVector3D>
#include <GLES2/gl2.h>


class Material;

class Mesh
{
public:
    Mesh(QString name,int triangle_count,GLfloat vertices[],GLfloat texcoords[],GLfloat normals[],
         GLuint vertex_vbo, GLuint texcoord_vbo, GLuint normal_vbo, Material *material);
    ~Mesh();

    void inc_count();
    void dec_count();
    long get_count();

    QString get_mesh_name();

    Material* get_material();
    void set_material(Material* mtl);

    int get_triangle_count();

    GLfloat* get_vertices();

    GLfloat* get_texcoords();

    GLfloat* get_normals();

    GLuint get_vertex_vbo();
    GLuint get_texcoord_vbo();
    GLuint get_normal_vbo();
    void set_vertex(int index, float x, float y, float z);
    float *get_vertex(int index);

    static long next_id();
    long get_id();

private:

    static long next_identifier;
    const long identifier;

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
