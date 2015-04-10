#version 400
//uniform mat4 V;
uniform sampler2D p_tex;
uniform sampler2D n_tex;
uniform sampler2D c_tex;
uniform vec3 ambient;
//uniform vec3 direction;
uniform vec2 win_size;

//was vec4
layout( location = 0 ) out vec3 frag_color;

void main () {
  vec2 st;
  st.s = gl_FragCoord.x / win_size.x;
  st.t = gl_FragCoord.y / win_size.y;
  vec4 p_texel = texture (p_tex, st);
  // skip background
  if (p_texel.z > -0.0001) {
    discard;
  }
  
  //vec4 n_texel = texture (n_tex, st);
  vec4 c_texel = texture (c_tex, st);
  
  
  //float dir = max(dot(n_texel.xyz,direction),0.0);
  
  frag_color.rgb = c_texel.rgb * ambient/* * dir*/;
  //frag_color.a = 1.0;  
}