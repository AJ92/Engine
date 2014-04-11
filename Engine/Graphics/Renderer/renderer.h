#ifndef RENDERER_H
#define RENDERER_H

#include "Graphics/OpenGL/OpenGL.h"

#include "Event/eventtransmitter.h"
#include <QString>

#include "Math/mathematics.h"
#include "Graphics/Model/model.h"
#include "Graphics/Camera/camera.h"
#include "Graphics/Window/window.h"
#include "Graphics/Model/modellibrary.h"
#include "Graphics/Model/lightlibrary.h"
#include "Graphics/Shader/shader.h"

//for frustum culling
#include "Graphics/Camera/frustum.h"
#include "Math/mathematics.h"

//for appdir
#include <QApplication>

class Renderer :  virtual public EventListener, virtual public EventTransmitter
{
public:

    enum PolygonModes {
        PolygonModeStandard     = 0x0001,
        PolygonModeVertex       = 0x0002,
        PolygonModeWireframe    = 0x0004
    };

    Renderer();
    ~Renderer();

    void initialize();

    void setModelLibrary(ModelLibrary * mdllib);
    void setLightLibrary(LightLibrary * lightlib);

    bool meshInFrustum(Frustum f, Model * mdl, Mesh * mesh, Matrix4x4 &pvm_mat);

    //renders the set ModelLibrary and LightLibrary
    void render();
    //render a model (inefficient compaired to a modellib rendering)
    void render(Model * m);

    void setCamera(Camera * cam);
    void setWindow(Window * win);

    void setPolygonMode(int polygonMode);

    Vector3 touch_to_space(int x,int y);

private:
    //old simple shaders
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


    int renderMode;


    //new DR stuff
    Matrix4x4 p_m;
    Matrix4x4 v_m;
    Matrix4x4 m_m;
    Matrix4x4 vm_m;
    Matrix4x4 pvm_m;

    GLfloat p_mat[16];
    GLfloat v_mat[16];
    GLfloat m_mat[16];
    GLfloat vm_mat[16];
    GLfloat pvm_mat[16];

    //COLOR PASS
    GLuint DR_FirstPassVertexShaderId;
    GLuint DR_FirstPassFragmentShaderId;
    GLuint DR_FirstPassProgramIdId;

    GLuint p_mat_loc_firtpass;
    GLuint v_mat_loc_firtpass;
    GLuint m_mat_loc_firtpass;
    GLuint vm_mat_loc_firtpass;



    //DEFERRED LIGHTING PASS
    GLuint DR_SecondPassVertexShaderId;
    GLuint DR_SecondPassFragmentShaderId;
    GLuint DR_SecondPassProgramIdId;

    GLuint p_mat_loc_secondpass;
    GLuint v_mat_loc_secondpass;
    GLuint m_mat_loc_secondpass;
    GLuint pvm_mat_loc_secondpass;

    GLuint lp_loc_secondpass;
    GLuint ld_loc_secondpass;
    GLuint ls_loc_secondpass;

    GLuint win_size_loc_secondpass;

    //DEFERRED AMBIENT PASS
    GLuint DR_AmbientPassVertexShaderId;
    GLuint DR_AmbientPassFragmentShaderId;
    GLuint DR_AmbientPassProgramIdId;

    GLuint color_loc_ambientpass;
    GLuint win_size_loc_ambientpass;


    //DEFERRED DIRECTIONALAMBIENT PASS
    GLuint DR_DirectionalAmbientPassVertexShaderId;
    GLuint DR_DirectionalAmbientPassFragmentShaderId;
    GLuint DR_DirectionalAmbientPassProgramIdId;

    GLuint v_mat_loc_directionalambientpass;

    GLuint dir_loc_directionalambientpass;
    GLuint color_loc_directionalambientpass;
    GLuint win_size_loc_directionalambientpass;


    //DEFERRED DEBUG PASS
    GLuint DR_DebugPassVertexShaderId;
    GLuint DR_DebugPassFragmentShaderId;
    GLuint DR_DebugPassProgramIdId;

    GLuint pvm_mat_loc_debugpass;

    GLuint color_loc_debugpass;


    //framebuffer textures
    GLuint fb;
    GLuint fb_tex_p;
    GLuint fb_tex_n;
    GLuint fb_tex_c;


    //renderbuffer
    GLuint rb;


    //ModelLibrary
    ModelLibrary * mdllib;

    //LightLibrary
    LightLibrary * lightlib;

    //camera and window
    Camera * cam;
    Window * win;



    bool createShaders();
    void destroyShaders();

    bool createBuffers();

    bool shadersAndBuffersCreated;

    void resizeBuffers(int x, int y);

    /*
    void createVBO();
    void destroyVBO();
    */

    void debugMessage(QString message);
    void eventRecieved(Event e);

    typedef struct
    {
        float XYZW[4];
        float RGBA[4];
    } Vertex;




    bool loaded_debug;


    //DEBUG STUFF
    Model * m_ntl;
    Model * m_ntr;
    Model * m_nbl;
    Model * m_nbr;

    Model * m_ftl;
    Model * m_ftr;
    Model * m_fbl;
    Model * m_fbr;

};

#endif // RENDERER_H
