#version 400
uniform sampler2D sampler1;
uniform sampler2D sampler2;
in vec2 t_eye;
in vec3 p_eye;
in vec3 n_eye;
in vec3 ta_eye;
in vec3 bta_eye;

in float logz;

layout( location = 0 ) out vec3 def_p;
layout( location = 1 ) out vec3 def_n;
layout( location = 2 ) out vec3 def_c;
layout( location = 3 ) out vec3 def_d;


mat3 buildTangentFrame(vec3 normal, vec3 binormal, vec3 tangent){
   return mat3(
      tangent,
      binormal,
      normal
   );  
}

//old logarithmic depth used in vertex shader...
/*
const float farPlane = 100000.0;

float logzbuf( vec4 xyzw)
{ 
   //this sshould be precalculated on the cpu side and passed in as a uniform...
   float invfarplanecoef = 2.0f / log(farPlane + 1);
   return (log(1 + xyzw.w) * invfarplanecoef - 1) * xyzw.w;
}
*/


void main () {
   vec4 c_eye = texture2D(sampler1, t_eye.st);
   vec3 c_normal = normalize(texture2D(sampler2, t_eye.st).rgb * 2.0 - 1.0);
   c_normal = vec3(c_normal.x, -c_normal.y, c_normal.z);


   mat3 tbnMatrix = buildTangentFrame(n_eye,bta_eye,ta_eye);
   //mat3 tbnMatrix = buildTangentFrame2(n_eye,bta_eye,ta_eye);
   def_n = (tbnMatrix * c_normal); 



   def_p = p_eye;
   def_c = c_eye.rgb;


   //depth 
   //gl_FragDepth = gl_FragCoord.z;
   //if we dont render geometry the depth will be 0
   //so we invert the depth -> white is close and black is far
   def_d.rgb = vec3(1.0 - gl_FragCoord.z);


   //logarithmic depth
   //gl_FragDepth = log(logz)*CF; 
   gl_FragDepth = logz;
}