#version 400
uniform sampler2D sampler1;
in vec2 t_eye;
in vec3 p_eye;
in vec3 n_eye;
layout( location = 0 ) out vec3 def_p;
layout( location = 1 ) out vec3 def_n;
layout( location = 2 ) out vec3 def_c;
void main () {

   vec4 c_eye = texture2D(sampler1, t_eye.st);
   if(c_eye.a > 0.01){
   	def_p = p_eye;
   	def_n = n_eye;
   	def_c = c_eye.rgb;
   }
   else{
   	discard;
   }
}