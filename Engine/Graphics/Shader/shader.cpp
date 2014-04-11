#include "shader.h"

Shader::Shader(QString shaderPath, GLenum shaderType) :
    Object(),
    shader_path(shaderPath),
    shader_type(shaderType),
    error_string("None"),
    m_shader_id(0),
    created(false)
{
    //load the shader source code.
    if(!load_shader_source(shaderPath)){
        return;
    }


    //create the shader, load the source and compile it
    m_shader_id = glCreateShader(shaderType);
    glShaderSource(m_shader_id, 1, &shader_source, NULL);
    glCompileShader(m_shader_id);

    //check if we could compile the stuff...
    GLint compiled;
    glGetShaderiv(m_shader_id, GL_COMPILE_STATUS, &compiled);
    if (compiled){
        error_string = "compiled successfully";
        created = true;
    }
    else{
        error_string = "compile failed\n";
        char messages[256];
        glGetShaderInfoLog(m_shader_id, sizeof(messages), 0, &messages[0]);
        error_string = error_string + QString::fromLatin1(messages);
    }

}

Shader::~Shader(){
    //TODO:
    //destroy the shader...
}

QString Shader::getShaderPath(){
    return shader_path;
}

GLuint Shader::getShaderId(){
    return m_shader_id;
}

GLenum Shader::getShaderType(){
    return shader_type;
}

const char * Shader::getShaderSource(){
    return shader_source;
}


bool Shader::isCreated(){
    return created;
}

QString Shader::getError(){
    return error_string;
}


//private:
bool Shader::load_shader_source(QString path){
    //load the source code of the shader.

    QFile shaderfile(path);
    if (!shaderfile.open(QFile::ReadOnly)) {
        error_string = "Shader: Unable to open file" + path;
        return false;
    }

    QByteArray shader_content = shaderfile.readAll();
    shader_source = shader_content.constData();

    return true;
}
