#ifndef SHADER_H
#define SHADER_H

#include <QString>
#include "Object/object.h"

#include "Graphics/Camera/camera.h"
#include "Graphics/Model/model.h"
#include "Graphics/Model/Components/mesh.h"
#include "Graphics/Model/Components/material.h"

#include "Graphics/OpenGL/OpenGL.h"

class Shader : public Object
{
public:
    Shader();
    /*
    Shader(QString name, QString vertex_shader_path, QString fragment_shader_path);
    virtual ~Shader();

    //Standart vertex and fragment shader for objects
    QString get_shader_name();
    GLuint get_program();

    //data transmission funcs
    void set(Camera* cam);
    void set(Model* mdl);
    void set(Mesh* msh);
    void set(Material* mtl);
    //render funcs
    virtual void set_stats();
    virtual void set_mat();
    virtual void set_data();
    virtual void draw();
    virtual void set_back();


protected:
    QString load_shader_source(QString path);
    bool set_program();
    bool link_program();
    bool check_status();
    bool created;
    QString shader_name;
    GLuint m_program;
    GLuint m_standart_v_shader;
    GLuint m_standart_f_shader;
    QString path_to_vertex_shader;
    QString path_to_fragment_shader;

    //window data pointer:
    //GLwindow* window;
    //camera data pointer:
    Camera* camera;
    //model data pointer:
    Model* model;
    Mesh* mesh;
    Material* material;
    */
};

#endif // SHADER_H
