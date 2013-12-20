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
}

Renderer::~Renderer(){
    //destructor:
    destroyShaders();
}



void Renderer::render(){

}

void Renderer::createShaders(){
    debugMessage("creating shaders...");
    GLenum ErrorCheckValue = glGetError();

    VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
    glCompileShader(VertexShaderId);

    FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
    glCompileShader(FragmentShaderId);

    ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);
    glLinkProgram(ProgramId);
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


void Renderer::debugMessage(QString message){
    Event e(Event::EventDebuggerMessage);
    e.setString(message);
    this->transmit(e);
}
