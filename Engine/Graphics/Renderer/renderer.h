#ifndef RENDERER_H
#define RENDERER_H

#include "Graphics/OpenGL/OpenGL.h"

#include "Event/eventtransmitter.h"
#include <QString>

#include "Math/mathematics.h"
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

class Light;
class Model;
class Material;
class Mesh;
class Event;
class Positation;
class CompositeObject;
class ObjectWorld;

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

    //next 2 will be removed ...
    void setModelLibrary(ModelLibrary * mdllib);
    void setLightLibrary(LightLibrary * lightlib);

    void setObjectWorld(ObjectWorld * objectworld);

    bool meshInFrustum(Frustum f, Model * mdl, Mesh * mesh, Matrix4x4 &pvm_mat);

    //render the objectWorld
    void render_v2();


    //renders the set ModelLibrary and LightLibrary
    void render();
    //render a model (inefficient compaired to a modellib rendering)
    void render(Model * m);

    void setCamera(Camera * cam);
    void setWindow(Window * win);

    void setPolygonMode(int polygonMode);

    Vector3 touch_to_space(int x,int y);


    int getMeshPerFrameCount();
    int getTrianglesPerFrameCount();

private:
    //old simple shaders
    const GLchar* VertexShader;
    const GLchar* FragmentShader;

    GLuint VertexShaderId;
    GLuint FragmentShaderId;
    GLuint ProgramId;


    //fsq = full screen quad (actually 2 triangles)
    //pointer to float arrays
    GLuint triangle_count;

    GLfloat* fsq_vertices;
    GLfloat* fsq_texcoords;
    GLfloat* fsq_normals;

    //vertex buffer objects (vertices, texcoords and normals)
    GLuint fsq_vertex_vbo;
    GLuint fsq_texcoord_vbo;
    GLuint fsq_normal_vbo;

    GLuint fsq_vertex_array_object;




    //TEXTURE INDICES FOR glActiveTexture
    GLuint firstTextureIndex;
    GLuint secondTextureIndex;
    GLuint thirdTextureIndex;
    GLuint fourthTextureIndex;

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



    //the world all object live in...
    ObjectWorld * objectworld;


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



    //debug
    int meshPerFrameCount;
    int trianglesPerFrameCount;
};

#endif // RENDERER_H
