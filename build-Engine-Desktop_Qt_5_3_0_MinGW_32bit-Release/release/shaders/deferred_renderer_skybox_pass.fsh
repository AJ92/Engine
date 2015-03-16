#version 400
uniform samplerCube sampler1;
in vec3 t_eye;
in vec3 p_eye;
in vec3 n_eye;
layout( location = 0 ) out vec3 def_p;
layout( location = 1 ) out vec3 def_n;
layout( location = 2 ) out vec3 def_c;
void main () {

   	vec4 c_eye = texture(sampler1, t_eye);
   	def_p = p_eye;
   	def_n = vec3(0.33,0.33,0.33);
   	def_c = c_eye.rgb;
}