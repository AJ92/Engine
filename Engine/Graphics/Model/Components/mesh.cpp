#include "mesh.h"

Mesh::Mesh(QString name, int triangle_count,
           GLfloat vertices[], GLfloat texcoords[],
           GLfloat normals[], GLfloat tangents[],
           GLfloat bitangents[], SP<Material> material) :
    loaded(false)
{
    mesh_name = name;

    this->triangle_count = triangle_count;

    this->vertices  = vertices;
    this->texcoords = texcoords;
    this->normals   = normals;

    this->tangents   = tangents;
    this->bitangents = bitangents;

    this->material  = material;
}

Mesh::~Mesh(){
    //delete material;

    material = NULL;
    glDeleteBuffers(1,&vertex_vbo);
    glDeleteBuffers(1,&texcoord_vbo);
    glDeleteBuffers(1,&normal_vbo);
    glDeleteBuffers(1,&tangent_vbo);
    glDeleteBuffers(1,&bitangent_vbo);
    vertex_vbo = 0;
    texcoord_vbo = 0;
    normal_vbo = 0;
    tangent_vbo = 0;
    bitangent_vbo = 0;
    delete [] vertices;
    delete [] texcoords;
    delete [] normals;
    delete [] tangents;
    delete [] bitangents;
    vertices = NULL;
    texcoords = NULL;
    normals = NULL;
    tangents = NULL;
    bitangents = NULL;
}

QString Mesh::get_name(){
    return mesh_name;
}

SP<Material> Mesh::get_material(){
    return material;
}

void Mesh::set_material(SP<Material> mtl){
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

GLfloat* Mesh::get_tangents(){
    return tangents;
}

GLfloat* Mesh::get_bitangents(){
    return bitangents;
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

GLuint Mesh::get_tangent_vbo(){
    return tangent_vbo;
}

GLuint Mesh::get_bitangent_vbo(){
    return bitangent_vbo;
}

GLuint Mesh::get_vertex_array_object(){
    return vertex_array_object;
}

void Mesh::loadGLdata(){

    qDebug("loading mesh");

    glGenVertexArrays(1, &vertex_array_object);

    glBindVertexArray(vertex_array_object);

    glGenBuffers(1, &vertex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, triangle_count * 3* 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //glEnableVertexAttribArray(0);


    glGenBuffers(1, &texcoord_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, texcoord_vbo);
    glBufferData(GL_ARRAY_BUFFER, triangle_count * 3 * 3 * sizeof(GLfloat), texcoords, GL_STATIC_DRAW);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //glEnableVertexAttribArray(1);


    glGenBuffers(1, &normal_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, normal_vbo);
    glBufferData(GL_ARRAY_BUFFER, triangle_count * 3 * 3 * sizeof(GLfloat), normals, GL_STATIC_DRAW);
    //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //glEnableVertexAttribArray(2);

    glGenBuffers(1, &tangent_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, tangent_vbo);
    glBufferData(GL_ARRAY_BUFFER, triangle_count * 3 * 3 * sizeof(GLfloat), tangents, GL_STATIC_DRAW);
    //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //glEnableVertexAttribArray(2);

    glGenBuffers(1, &bitangent_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, bitangent_vbo);
    glBufferData(GL_ARRAY_BUFFER, triangle_count * 3 * 3 * sizeof(GLfloat), bitangents, GL_STATIC_DRAW);
    //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //glEnableVertexAttribArray(2);

    qDebug("loaded mesh!");

    loaded = true;
}

bool Mesh::isLoaded(){
    return loaded;
}

//TODO: update this, because it should change tangents and bitangents aswell !!!
/*
generateNormalAndTangent(float3 v1, float3 v2, text2 st1, text2 st2)
{
    float3 normal = v1.crossProduct(v2);

    float coef = 1/ (st1.u * st2.v - st2.u * st1.v);
    float3 tangent;

    tangent.x = coef * ((v1.x * st2.v)  + (v2.x * -st1.v));
    tangent.y = coef * ((v1.y * st2.v)  + (v2.y * -st1.v));
    tangent.z = coef * ((v1.z * st2.v)  + (v2.z * -st1.v));

    float3 binormal = normal.crossProduct(tangent);
}
*/


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


Vector3 Mesh::getBoundingSpherePos(){
    return bounding_sphere_position;
}

double Mesh::getBoundingSphereRadius(){
    return bounding_sphere_radius;
}

void Mesh::setBoundingSpherePos(Vector3 pos){
    this->bounding_sphere_position = pos;
}

void Mesh::setBoundingSphereRadius(double radius){
    this->bounding_sphere_radius = radius;
}
