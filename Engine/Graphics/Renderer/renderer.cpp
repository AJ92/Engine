#include "renderer.h"


Renderer::Renderer() :
    EventTransmitter()
{

}

void Renderer::initialize(){
    debugMessage("loading shader sources...");
    /*
    VertexShader =
            "#version 400\n"\

            "layout(location=0) in vec4 in_Position;\n"\
            "layout(location=1) in vec4 in_Color;\n"\
            "out vec4 ex_Color;\n"\

            "void main(void)\n"\
            "{\n"\
            "	gl_Position = in_Position;\n"\
            "	ex_Color = in_Color;\n"\
            "}\n";
    FragmentShader =
            "#version 400\n"\

            "in vec4 ex_Color;\n"\
            "out vec4 out_Color;\n"\

            "void main(void)\n"\
            "{\n"\
            "	out_Color = ex_Color;\n"\
            "}\n";

            */


    //standard shader
    VertexShader =
            "#version 400\n"\
            "layout(location=0) in vec4 vertex;"\
            "layout(location=1) in vec2 texcoord;"\
            "layout(location=2) in vec3 normal;"\
            "uniform mat4 mvp_matrix;"\
            "uniform mat4 norm_matrix;"\
            "out vec2 texc;"\
            "out float dir;"\
            "void main(void)"\
            "{"\
            "    texc = texcoord;"\
            "    vec3 ldir = normalize(norm_matrix * vec4(0.0,0.0,1.0,0.0)).xyz;"\
            "    dir = max(dot(normal.xyz,ldir),0.0);"\
            "    gl_Position =  mvp_matrix * vertex;"\
            "}";
    FragmentShader =
            "#version 400\n"\
            "uniform sampler2D sampler1;"\
            "in vec2 texc;"\
            "in float dir;"\
            "layout( location = 0 ) out vec4 FragColor;"\
            "void main(void)"\
            "{"\
            "    vec3 color = texture2D(sampler1, texc.st).rgb;"\
            "    FragColor = vec4((color*0.1)+(color*dir*1.1),1.0);"\
            "}";


    createShaders();
    //createVBO();
}

Renderer::~Renderer(){
    //destructor:
    destroyShaders();
    //destroyVBO();
}


void Renderer::setCamera(Camera * cam){
    this->cam = cam;
}

void Renderer::setWindow(Window * win){
    this->win = win;
}


void Renderer::render(Model * m){

    if(m->isReadyToRender()){
        GLenum ErrorCheckValue = glGetError();
        if (ErrorCheckValue != GL_NO_ERROR)
        {
            debugMessage("ERROR before rendering: " + QString((char*) gluErrorString(ErrorCheckValue)));
        }


        QList<Mesh*> meshs = m->get_meshs();

        m_p.set_to_identity();
        m_p.perspective(cam->FOV, float(win->getWindowWidth()) / float(win->getWindowHeight()),
                        cam->Z_NEAR, cam->Z_FAR);

        m_mvp =cam->M_camera_view.inverted() * m->get_model_matrix();
        m_norm = m_mvp.inverted();
        m_mvp = m_p * m_mvp;

        for (int f = 0; f < 4; f++) {
            for (int g = 0; g < 4; g++) {
                mvp_mat[f * 4 + g] = (GLfloat) (m_mvp[f*4+g]);
                norm_mat[f * 4 + g] = (GLfloat) (m_norm[f*4+g]);
            }
        }


        glUniformMatrix4fv(mvp_mat_loc, 1, GL_FALSE, mvp_mat);
        glUniformMatrix4fv(norm_mat_loc, 1, GL_FALSE, norm_mat);



        for(int i = 0; i < meshs.size(); i++){

            Mesh * mesh = meshs.at(i);


            //tex
            glBindTexture(GL_TEXTURE_2D, mesh->get_material()->get_diffuse_map_texture());

            //sample 2d
            glUniform1i(samp2d_loc, 0);


            //VAO

            glBindVertexArray(mesh->get_vertex_array_object());

            //VBOs
            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_vbo());
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_texcoord_vbo());
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_normal_vbo());
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(2);

            glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
        }

        ErrorCheckValue = glGetError();
        if (ErrorCheckValue != GL_NO_ERROR)
        {
            debugMessage("ERROR after rendering: " + QString((char*) gluErrorString(ErrorCheckValue)));
        }
    }
}


void Renderer::setPolygonMode(PolygonModes polygonMode){
    if(polygonMode == PolygonModePoint){
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
    else if(polygonMode == PolygonModeLine){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else if(polygonMode == PolygonModeFill){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}


void Renderer::createShaders(){
    debugMessage("creating shaders...");
    GLenum ErrorCheckValue = glGetError();

    VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
    glCompileShader(VertexShaderId);

    GLint compiled;

    glGetShaderiv(VertexShaderId, GL_COMPILE_STATUS, &compiled);
    debugMessage(QString::number(compiled));
    if (compiled){
        debugMessage("vshader compiled");
    }
    else{
        debugMessage("vshader compile failed!!!");
        char messages[256];
        glGetShaderInfoLog(VertexShaderId, sizeof(messages), 0, &messages[0]);
        debugMessage(QString(messages));
    }



    FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
    glCompileShader(FragmentShaderId);

    glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &compiled);
    debugMessage(QString::number(compiled));
    if (compiled){
        debugMessage("fshader compiled");
    }
    else{
        debugMessage("fshader compile failed!!!");
        char messages[256];
        glGetShaderInfoLog(FragmentShaderId, sizeof(messages), 0, &messages[0]);
        debugMessage(QString(messages));
    }



    ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);


    // Bind the custom vertex attributes
    glBindAttribLocation(ProgramId, 0, "vertex");
    glBindAttribLocation(ProgramId, 1, "texCoord");
    glBindAttribLocation(ProgramId, 2, "normal");





    glLinkProgram(ProgramId);

    GLint linked;
    glGetProgramiv(ProgramId, GL_LINK_STATUS, &linked);
    debugMessage(QString::number(linked));
    if (linked){
        debugMessage("program linked");
    }
    else{
        debugMessage("program linking failed!!!");
        char messages[256];
        glGetProgramInfoLog(ProgramId, sizeof(messages), 0, &messages[0]);
        debugMessage(QString(messages));
    }

    glUseProgram(ProgramId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR(3): Could not create the shaders: " + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return;
    }




    glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_TRUE);


    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    mvp_mat_loc = glGetUniformLocation(ProgramId, "mvp_matrix");
    norm_mat_loc = glGetUniformLocation(ProgramId, "norm_matrix");
    samp2d_loc = glGetUniformLocation(ProgramId, "sampler1");

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR: after Shader: " + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return;
    }
}

void Renderer::destroyShaders(){
    debugMessage("destroying shaders...");
    GLenum ErrorCheckValue = glGetError();

    glUseProgram(0);

    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);

    glDeleteShader(FragmentShaderId);
    glDeleteShader(VertexShaderId);

    glDeleteProgram(ProgramId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR(4): Could not destroy the shaders: "  + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return;
    }
}

/*
void Renderer::createVBO(){
    Vertex Vertices[] =
    {
        { { -0.8f, -0.8f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        { {  0.0f,  0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { {  0.8f, -0.8f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
    };

    GLenum ErrorCheckValue = glGetError();
    const size_t BufferSize = sizeof(Vertices);
    const size_t VertexSize = sizeof(Vertices[0]);
    const size_t RgbOffset = sizeof(Vertices[0].XYZW);


    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);


    glGenBuffers(1, &VboId);
    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR(5): Could not create a VBO: " + QString((char*) gluErrorString(ErrorCheckValue)));
        exit(EXIT_FAILURE);
    }

}

void Renderer::destroyVBO(){
    GLenum ErrorCheckValue = glGetError();

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VboId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR(6): Could not destroy the VBO: " + QString((char*) gluErrorString(ErrorCheckValue)));
        exit(EXIT_FAILURE);
    }
}
*/

void Renderer::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}
