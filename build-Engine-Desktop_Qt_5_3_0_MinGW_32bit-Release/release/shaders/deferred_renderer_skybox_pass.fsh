#version 400
uniform samplerCube sampler1;

in vec3 t_eye;

layout( location = 0) out vec3 def_c;

void main () {
   	vec4 c_eye = texture(sampler1, t_eye);
	def_c = c_eye.rgb;
}