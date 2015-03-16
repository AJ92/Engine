#version 400 

layout(location=0) in vec4 vp; 
layout(location=1) in vec2 vt; 
layout(location=2) in vec3 vn; 
uniform mat4 P, V, M, VM;

out vec3 t_eye;
out vec3 p_eye; 
out vec3 n_eye; 

void main () { 
   p_eye = (VM * vp).xyz; 
   n_eye = (VM * vec4 (0.0,0.0,1.0,0.0)).xyz; 
   t_eye = vp.xyz * 0.1; 
   gl_Position = P * V * M *  vec4 (vp.xyz, 1.0); 
}