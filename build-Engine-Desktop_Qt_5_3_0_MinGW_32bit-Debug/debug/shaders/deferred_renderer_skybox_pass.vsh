#version 400 

layout(location=0) in vec4 vp; 
uniform mat4 P, V, M, VM;

out vec3 t_eye;

void main () { 
   t_eye = vp.xyz * 0.1; 
   gl_Position = P * V * M *  vec4 (vp.xyz, 1.0); 
}