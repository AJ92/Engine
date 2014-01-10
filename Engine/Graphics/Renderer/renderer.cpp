#include "renderer.h"


Renderer::Renderer() :
    EventTransmitter()
{

}

void Renderer::initialize(){
    debugMessage("loading shader sources...");
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
    createShaders();
    createVBO();
}

Renderer::~Renderer(){
    //destructor:
    destroyShaders();
    destroyVBO();
}



void Renderer::render(){
    glDrawArrays(GL_TRIANGLES, 0, 3);
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
        exit(EXIT_FAILURE);
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
        exit(EXIT_FAILURE);
    }
}

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


void Renderer::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    EventDebugger * ed = new EventDebugger(message);
    e.debugger = ed;
    this->transmit(e);
}
