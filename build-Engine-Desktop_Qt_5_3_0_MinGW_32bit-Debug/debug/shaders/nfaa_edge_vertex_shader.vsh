#version 400
layout(location=0) in vec4 vp;
layout(location=1) in vec2 vt;
layout(location=2) in vec3 vn;
void main () {
	gl_Position = vp;
}