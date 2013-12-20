#ifndef RENDERER_H
#define RENDERER_H

#include "Graphics/glew/include/GL/glew.h"
#include "Graphics/freeglut/include/GL/freeglut.h"

#include "Event/eventtransmitter.h"
#include <QString>

class Renderer : virtual public EventTransmitter
{
public:
    Renderer();
    ~Renderer();

    void initialize();
    void render();

private:
    const GLchar* VertexShader;
    const GLchar* FragmentShader;

    GLuint VertexShaderId;
    GLuint FragmentShaderId;
    GLuint ProgramId;
    GLuint VaoId;
    GLuint VboId;


    void createShaders();
    void destroyShaders();

    void debugMessage(QString message);
};

#endif // RENDERER_H
