#version 400 

layout(location=0) in vec4 vp; 
layout(location=1) in vec2 vt; 
layout(location=2) in vec3 vn; 
uniform mat4 P, V, M, VM;

out vec2 t_eye;
out vec3 p_eye; 
out vec3 n_eye; 

void main () { 
   p_eye = (VM * vp).xyz; 
   n_eye = (VM * vec4 (vn, 0.0)).xyz; 
   t_eye = vt; 
   gl_Position = P * vec4 (p_eye, 1.0); 
}