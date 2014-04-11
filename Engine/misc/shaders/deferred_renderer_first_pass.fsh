#version 400
uniform sampler2D sampler1;
in vec2 t_eye;
in vec3 p_eye;
in vec3 n_eye;
layout( location = 0 ) out vec3 def_p;
layout( location = 1 ) out vec3 def_n;
layout( location = 2 ) out vec3 def_c;
void main () {
   def_p = p_eye;
   def_n = n_eye;
   vec3 c_eye = texture2D(sampler1, t_eye.st).rgb;
   def_c = c_eye;
}