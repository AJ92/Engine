#version 400
layout(location=0) in vec4 vp;
layout(location=1) in vec2 vt;
layout(location=2) in vec3 vn;
//uniform mat4 P, V, M, PVM;
void main () {
	/*
    const vec4 verts[4] = vec4[4](vec4(-1.0, -1.0, 0.5, 1.0),
                                  vec4( 1.0, -1.0, 0.5, 1.0),
                                  vec4(-1.0,  1.0, 0.5, 1.0),
                                  vec4( 1.0,  1.0, 0.5, 1.0));
  */                                

  	//gl_Position = verts[gl_VertexID];
	gl_Position = vp;
}