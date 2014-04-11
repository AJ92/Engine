#ifndef SHADER_H
#define SHADER_H

#include <QString>
#include "Object/object.h"
#include "Graphics/OpenGL/OpenGL.h"

//so we can loud the source code
#include <QFile>
#include <QTextStream>
#include <QByteArray>

class Shader : public Object
{
public:
    Shader();

    Shader(QString shaderPath, GLenum shaderType);
    virtual ~Shader();

    QString getShaderPath();
    GLuint getShaderId();
    GLenum getShaderType();

    const char * getShaderSource();

    bool isCreated();
    QString getError();

private:
    bool load_shader_source(QString path);

    bool created;
    GLenum shader_type;
    QString shader_path;
    QString error_string;
    GLuint m_shader_id;

    const char * shader_source;
};

#endif // SHADER_H
