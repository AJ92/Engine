#version 400
uniform mat4 V;
uniform sampler2D p_tex;
uniform sampler2D n_tex;
uniform sampler2D c_tex;
uniform vec3 ambient;
uniform vec3 direction;
uniform vec2 win_size;

//was vec4
layout( location = 3 ) out vec3 frag_color;
const vec3 kd = vec3 (1.0, 1.0, 1.0);
void main () {
  vec2 st;
  st.s = gl_FragCoord.x / win_size.x;
  st.t = gl_FragCoord.y / win_size.y;

  /*
  vec4 p_texel = texture (p_tex, st);
  // skip background
  if (p_texel.z > -0.0001) {
    discard;
  }
  vec4 n_texel = texture (n_tex, st);
  vec4 c_texel = texture (c_tex, st);
  
  vec3 ldir = normalize(V * vec4(direction,0.0)).xyz;
  float dir = max(dot(n_texel.xyz,ldir),0.0);
  
  frag_color.rgb = c_texel.rgb * ambient * dir;
  frag_color.a = 1.0;
  */


  vec4 p_texel = texture (p_tex, st);
  vec4 c_texel = texture (c_tex, st);
  vec4 n_texel = texture (n_tex, st);
  // skip background
  if (p_texel.z > -0.0001) {
    discard;
  }

  
  vec3 n_eye = normalize (n_texel).rgb;
  vec3 direction_to_light_eye = normalize(V * vec4(direction,0.0)).xyz;
  float dot_prod = max (dot (direction_to_light_eye,  n_eye), 0.0);
  vec3 Ia = ambient * kd * dot_prod;

  frag_color.rgb = c_texel.rgb * Ia;
  //frag_color.a = 1.0; 

}