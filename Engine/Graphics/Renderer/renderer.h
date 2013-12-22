#ifndef RENDERER_H
#define RENDERER_H

#include "Graphics/OpenGL/OpenGL.h"

#include "Event/eventtransmitter.h"
#include <QString>

class Renderer : virtual public EventTransmitter
{
public:

    enum PolygonModes {
        PolygonModePoint   = 0x00,
        PolygonModeLine    = 0x01,
        PolygonModeFill    = 0x02
    };

    Renderer();
    ~Renderer();

    void initialize();
    void render();

    void setPolygonMode(PolygonModes polygonMode);

private:
    const GLchar* VertexShader;
    const GLchar* FragmentShader;

    GLuint VertexShaderId;
    GLuint FragmentShaderId;
    GLuint ProgramId;
    GLuint VaoId;
    GLuint VboId;


    //next 4 funcs need to be outsourced
    void createShaders();
    void destroyShaders();

    void createVBO();
    void destroyVBO();

    void debugMessage(QString message);

    typedef struct
    {
        float XYZW[4];
        float RGBA[4];
    } Vertex;
};

#endif // RENDERER_H
