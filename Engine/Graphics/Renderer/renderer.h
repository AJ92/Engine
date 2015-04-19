#ifndef RENDERER_H
#define RENDERER_H

#include "Graphics/OpenGL/OpenGL.h"

#include "Event/eventtransmitter.h"
#include <QString>


#include "Vector/vector3.h"
#include "Matrix/matrix4x4.h"



#include "Graphics/Camera/camera.h"
#include "Graphics/Window/window.h"
#include "Graphics/Model/modellibrary.h"
#include "Graphics/Shader/shader.h"

//for frustum culling
#include "Graphics/Camera/frustum.h"


//for appdir
#include <QApplication>

#include "Object/SmartPointer/smartpointer.h"

#include "Object/positation.h"

class Light;
class Model;
class Material;
class TextureMap;
class TextureMapCube;
class Mesh;
class Event;

class CompositeObject;
class ObjectWorld;

class Renderer :  virtual public EventListener, virtual public EventTransmitter
{
public:

    enum PolygonModes {
        PolygonModeStandard         = 0x0001,
        PolygonModeVertex           = 0x0002,
        PolygonModeWireframe        = 0x0004,
        //additionl debug modes
        //light
        PolygonModeLightVertex      = 0x0008,
        PolygonModeLightWireframe   = 0x0010,
        //octtree
        PolygonModeOctTreeVertex    = 0x0020,
        PolygonModeOctTreeWireframe = 0x0040
    };

    enum PostProcessingModes {
        PostProcessingModeNone      = 0x0001,

        PostProcessingModeFXAA      = 0x0002,
        PostProcessingModeSharpen   = 0x0004,
        PostProcessingModeSSAO      = 0x0008,
        PostProcessingModeGrain     = 0x0010,
        PostProcessingModeBlurH     = 0x0020,
        PostProcessingModeBlurV     = 0x0040,

        PostProcessingModeMax       = 0x0080
    };

    Renderer();
    ~Renderer();

    void initialize();

    void setObjectWorld(SP<ObjectWorld> objectworld);

    bool meshInFrustum(SP<Frustum> f, SP<Model> mdl, SP<Mesh> mesh, Matrix4x4 &pvm_mat);

    //render the objectWorld
    void render_v2();



    //renders the set ModelLibrary and LightLibrary
    //void render();
    //render a model (inefficient compaired to a modellib rendering)
    void render(SP<Model> m);

    void setCamera(SP<Camera> cam);
    void setWindow(SP<Window> win);

    void setPolygonMode(int polygonMode);
    void setPostProcessingMode(int postProcessingMode);
    int getPostProcessingMode();

    Vector3 touch_to_space(int x,int y);


    int getMeshPerFrameCount();
    int getTrianglesPerFrameCount();
    int getTexBindsPerFrameCount();

private:
    //old simple shaders
    const GLchar* VertexShader;
    const GLchar* FragmentShader;

    GLuint VertexShaderId;
    GLuint FragmentShaderId;
    GLuint ProgramId;


    //fsq = full screen quad (actually 2 triangles)  
    GLuint fsq_triangle_count;
    //pointer to float arrays
    GLfloat* fsq_vertices;
    GLfloat* fsq_texcoords;
    GLfloat* fsq_normals;
    //vertex buffer objects (vertices, texcoords and normals)
    GLuint fsq_vertex_vbo;
    GLuint fsq_texcoord_vbo;
    GLuint fsq_normal_vbo;
    GLuint fsq_vertex_array_object;


    //sky box
    GLuint sb_triangle_count;
    //pointer to float arrays
    GLfloat* sb_vertices;
    //vertex buffer object (vertices)
    GLuint sb_vertex_vbo;
    GLuint sb_vertex_array_object;
    SP<TextureMapCube> sb_texmap;





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
    int postProcessingMode;


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


    //SIMPLE SKYBOX PASS (aka first color only pass...)
    GLuint DR_SkyBoxPassVertexShaderId;
    GLuint DR_SkyBoxPassFragmentShaderId;
    GLuint DR_SkyBoxPassProgramIdId;

    GLuint p_mat_loc_skyboxpass;
    GLuint v_mat_loc_skyboxpass;
    GLuint m_mat_loc_skyboxpass;
    GLuint vm_mat_loc_skyboxpass;



    //SIMPLE BUFFERCOPY PASS (copies one buffer to another)
    GLuint DR_BufferCopyPassVertexShaderId;
    GLuint DR_BufferCopyPassFragmentShaderId;
    GLuint DR_BufferCopyPassProgramIdId;

    GLuint win_size_loc_buffercopypass;



    //COLOR PASS
    GLuint DR_FirstPassVertexShaderId;
    GLuint DR_FirstPassFragmentShaderId;
    GLuint DR_FirstPassProgramIdId;

    GLuint p_mat_loc_firstpass;
    GLuint v_mat_loc_firstpass;
    GLuint m_mat_loc_firstpass;
    GLuint vm_mat_loc_firstpass;
    GLuint norm_mat_loc_firstpass;



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



    //DEFERRED POST PROCESSING pass
    GLuint DR_EdgeDetectionPassVertexShaderId;
    GLuint DR_EdgeDetectionPassFragmentShaderId;
    GLuint DR_EdgeDetectionPassProgramIdId;

    GLuint win_size_loc_edgedetectionpass;
    GLuint frame_switch_loc_edgedetectionpass;
    GLuint function_loc_edgedetectionpass;






//FIRST FBO

    //framebuffer textures
    GLuint fbo_1;
    GLuint fbo_1_tex_p;    //position
    GLuint fbo_1_tex_n;    //normal
    GLuint fbo_1_tex_c;    //color
    GLuint fbo_1_tex_d;    //depth


    //renderbuffer
    GLuint rb1;


//SECOND FBO

    //framebuffer textures
    GLuint fbo_2;
    GLuint fbo_2_tex_c;    //color1

    //renderbuffer
    GLuint rb2;


//THIRD FBO

    //framebuffer textures
    GLuint fbo_3;
    GLuint fbo_3_tex_c;    //color1

    //renderbuffer
    GLuint rb3;

    int frame_switch;





    //the world all object live in...
    SP<ObjectWorld> objectworld;


    //camera and window
    SP<Camera> cam;
    SP<Window> win;


    bool createFullScreenQuad();
    bool createSkyBox();

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
    int texBindsPerFrameCount;
};

#endif // RENDERER_H
