#ifndef RENDERER_H
#define RENDERER_H

#include "Graphics/OpenGL/OpenGL.h"

#include "Event/eventtransmitter.h"
#include <QString>

#include "Math/mathematics.h"
#include "Graphics/Model/model.h"
#include "Graphics/Camera/camera.h"
#include "Graphics/Window/window.h"

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

    void render(Model * m);

    void setCamera(Camera * cam);
    void setWindow(Window * win);

    void setPolygonMode(PolygonModes polygonMode);

private:
    const GLchar* VertexShader;
    const GLchar* FragmentShader;

    GLuint VertexShaderId;
    GLuint FragmentShaderId;
    GLuint ProgramId;



    //temporal
    GLuint mvp_mat_loc;
    GLuint norm_mat_loc;
    GLuint samp2d_loc;

    Matrix4x4 m_p;
    Matrix4x4 m_mvp;
    GLfloat mvp_mat[16];
    Matrix4x4 m_norm;
    GLfloat norm_mat[16];

    //camera and window
    Camera * cam;
    Window * win;


    //next 4 funcs need to be outsourced
    void createShaders();
    void destroyShaders();

    /*
    void createVBO();
    void destroyVBO();
    */

    void debugMessage(QString message);

    typedef struct
    {
        float XYZW[4];
        float RGBA[4];
    } Vertex;
};

#endif // RENDERER_H
