#version 400
uniform mat4 V;
uniform sampler2D p_tex;
uniform sampler2D n_tex;
uniform sampler2D c_tex;
uniform vec3 ls;
uniform vec3 ld;
uniform vec3 lp;
uniform vec2 win_size;

//was vec4
layout( location = 0 ) out vec3 frag_color;
const vec3 kd = vec3 (1.0, 1.0, 1.0);
const vec3 ks = vec3 (1.0, 1.0, 1.0);
const float specular_exponent = 100.0;

vec3 phong (in vec3 p_eye, in vec3 n_eye) {
  vec3 light_position_eye = vec3 (V * vec4 (lp, 1.0));
  vec3 dist_to_light_eye = light_position_eye - p_eye;
  vec3 direction_to_light_eye = normalize (dist_to_light_eye);
  
  // standard diffuse light
  float dot_prod = max (dot (direction_to_light_eye,  n_eye), 0.0);
  vec3 Id = ld * kd * dot_prod; // final diffuse intensity
  
  // standard specular light
  vec3 reflection_eye = reflect (-direction_to_light_eye, n_eye);
  vec3 surface_to_viewer_eye = normalize (-p_eye);
  float dot_prod_specular = dot (reflection_eye, surface_to_viewer_eye);
  dot_prod_specular = max (dot_prod_specular, 0.0);
  float specular_factor = pow (dot_prod_specular, specular_exponent);
  vec3 Is = ls * ks * specular_factor; // final specular intensity
  
  // attenuation (fade out to sphere edges)
  float dist_2d = distance (light_position_eye, p_eye);
   //175.0 is the spheres scale...
  float atten_factor = -log (min (1.0, dist_2d / (175.0 * 2.0)));
  
  return (Id + Is) * atten_factor;
}
void main () {
  vec2 st;
  st.s = gl_FragCoord.x / win_size.x;
  st.t = gl_FragCoord.y / win_size.y;
  vec4 p_texel = texture (p_tex, st);
  // skip background
  if (p_texel.z > -0.0001) {
    discard;
  }
  vec4 n_texel = texture (n_tex, st);
  
  vec4 c_texel = texture (c_tex, st);
  
  frag_color.rgb = c_texel.rgb * phong (p_texel.rgb, normalize (n_texel).rgb);
  //frag_color.a = 1.0;

}
