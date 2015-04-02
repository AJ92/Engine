#version 400
uniform sampler2D sampler1;
uniform sampler2D sampler2;
in vec2 t_eye;
in vec3 p_eye;
in vec3 n_eye;
in vec3 ta_eye;
in vec3 bta_eye;

layout( location = 0 ) out vec3 def_p;
layout( location = 1 ) out vec3 def_n;
layout( location = 2 ) out vec3 def_c;


mat3 buildTangentFrame(vec3 normal, vec3 binormal, vec3 tangent){
   return mat3(
      tangent,
      binormal,
      normal
   );  
}

mat3 buildTangentFrame2(vec3 normal, vec3 binormal, vec3 tangent){
   return mat3(
      normal.x, binormal.x, tangent.x,
      normal.y, binormal.y, tangent.y,
      normal.z, binormal.z, tangent.z

   );  
}



void main () {
   vec4 c_eye = texture2D(sampler1, t_eye.st);
   vec3 c_normal = normalize(texture2D(sampler2, t_eye.st).rgb * 2.0 - 1.0);
   c_normal = vec3(c_normal.x, -c_normal.y, c_normal.z);


   mat3 tbnMatrix = buildTangentFrame(n_eye,bta_eye,ta_eye);
   //mat3 tbnMatrix = buildTangentFrame2(n_eye,bta_eye,ta_eye);
   def_n = (tbnMatrix * c_normal); 



   def_p = p_eye;
   def_c = c_eye.rgb;
   //def_c = c_normal ;

}