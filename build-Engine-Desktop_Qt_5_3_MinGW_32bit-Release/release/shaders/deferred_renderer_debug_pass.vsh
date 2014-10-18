#version 400 

layout(location=0) in vec4 vp;  
uniform mat4 PVM;

void main () { 
   gl_Position = PVM * vp; 
}