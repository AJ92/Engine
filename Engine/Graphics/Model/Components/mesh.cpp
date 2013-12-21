#include "mesh.h"

Mesh::Mesh(QString name, int triangle_count, GLfloat vertices[], GLfloat texcoords[], GLfloat normals[], GLuint vertex_vbo, GLuint texcoord_vbo, GLuint normal_vbo, Material *material)
{
    mesh_name = name;

    this->triangle_count = triangle_count;

    this->vertices  = vertices;
    this->texcoords = texcoords;
    this->normals   = normals;

    this->material  = material;

    this->vertex_vbo = vertex_vbo;
    this->texcoord_vbo = texcoord_vbo;
    this->normal_vbo = normal_vbo;
}

Mesh::~Mesh(){
    //delete material;

    material = NULL;
    glDeleteBuffers(1,&vertex_vbo);
    glDeleteBuffers(1,&texcoord_vbo);
    glDeleteBuffers(1,&normal_vbo);
    vertex_vbo = NULL;
    texcoord_vbo = NULL;
    normal_vbo = NULL;
    delete [] vertices;
    delete [] texcoords;
    delete [] normals;
    vertices = NULL;
    texcoords = NULL;
    normals = NULL;
}

QString Mesh::get_name(){
    return mesh_name;
}

Material* Mesh::get_material(){
    return material;
}

void Mesh::set_material(Material* mtl){
    material = mtl;
}

int Mesh::get_triangle_count(){
    return triangle_count;
}

GLfloat* Mesh::get_vertices(){
    return vertices;
}

GLfloat* Mesh::get_texcoords(){
    return texcoords;
}

GLfloat* Mesh::get_normals(){
    return normals;
}

GLuint Mesh::get_vertex_vbo(){
    return vertex_vbo;
}

GLuint Mesh::get_texcoord_vbo(){
    return texcoord_vbo;
}

GLuint Mesh::get_normal_vbo(){
    return normal_vbo;
}


void Mesh::set_vertex(int index, float x, float y, float z){

    GLfloat* vertex = new GLfloat[3];
    vertex[0] = (GLfloat) x;
    vertex[1] = (GLfloat) y;
    vertex[2] = (GLfloat) z;

    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*3*index, sizeof(float)*3, vertex);

    vertices[index*3]   = (GLfloat) x;
    vertices[index*3+1] = (GLfloat) y;
    vertices[index*3+2] = (GLfloat) z;
}

void Mesh::set_vertex(int index, Vector3 vector){
    set_vertex(index, vector.x(), vector.y(), vector.z());
}

Vector3 Mesh::get_vertex(int index){
    return Vector3((float) vertices[index*3],
                   (float) vertices[index*3+1],
                   (float) vertices[index*3+2]);
}
