attribute lowp vec4 vertex;
attribute lowp vec2 texcoord;
attribute lowp vec3 normal;
uniform highp mat4 mvp_matrix;
uniform highp mat4 norm_matrix;
varying lowp vec2 texc;
varying lowp float dir;
void main(void)
{
	texc = texcoord;
	vec3 ldir = normalize(norm_matrix * vec4(0.0,0.0,1.0,0.0)).xyz;
	dir = max(dot(normal.xyz,ldir),0.0);
	gl_Position =  mvp_matrix * vertex;
}
