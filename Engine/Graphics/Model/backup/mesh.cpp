#include "mesh.h"

long Mesh::next_identifier = 0;

Mesh::Mesh(QString name,int triangle_count,GLfloat vertices[],GLfloat texcoords[],GLfloat normals[],
           GLuint vertex_vbo,GLuint texcoord_vbo, GLuint normal_vbo, Material *material):
    identifier(next_id())
{

    qDebug("\n\nnew mesh\nMESH ID: %d",identifier);

    mesh_name = name;
    this->triangle_count = triangle_count;
    this->vertices  = vertices;
    this->texcoords = texcoords;
    this->normals   = normals;

    this->material  = material;

    this->vertex_vbo = vertex_vbo;
    this->texcoord_vbo = texcoord_vbo;
    this->normal_vbo = normal_vbo;

    /*
    qDebug("## new mesh ##");
    int face = 0;
    for(int k = 0; k < triangle_count*3; k+=3){
        qDebug(QString::number(face).toUtf8() + ":   " +
                 QString::number(this->vertices[k]).toUtf8() + " " +
                 QString::number(this->vertices[k+1]).toUtf8() + " " +
                 QString::number(this->vertices[k+2]).toUtf8());
        face += 1;
    }
    */
}

Mesh::~Mesh(){
    qDebug("Mesh DESTRUCTOR CALLED");

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


    qDebug("Mesh DESTRUCTOR FINISHED");
}

long Mesh::next_id(){
    next_identifier++;
    return next_identifier;
}

long Mesh::get_id(){
    return identifier;
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

QString Mesh::get_mesh_name(){
    return mesh_name;
}

Material* Mesh::get_material(){
    return material;
}

void Mesh::set_vertex(int index, float x, float y, float z){

    GLfloat* vertex = new GLfloat[3];
    vertex[0] = (GLfloat) x;
    vertex[1] = (GLfloat) y;
    vertex[2] = (GLfloat) z;

    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*3*index, sizeof(float)*3, vertex);

    vertices[index*3]   = (GLfloat)x;
    vertices[index*3+1] = (GLfloat)y;
    vertices[index*3+2] = (GLfloat)z;
}

float* Mesh::get_vertex(int index){
    float* vertex = new float[3];
    vertex[0] = (float) vertices[index*3];
    vertex[1] = (float) vertices[index*3+1];
    vertex[2] = (float) vertices[index*3+2];
    return vertex;
}

void Mesh::set_material(Material* mtl){
    material = mtl;
}
