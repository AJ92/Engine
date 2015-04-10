#version 400 

layout(location=0) in vec4 vp; 		//vertex pos
layout(location=1) in vec2 vt; 		//vertex texture coordinates
layout(location=2) in vec3 vn; 		//vertex normal
layout(location=3) in vec3 vta; 	//vertex tangent
layout(location=4) in vec3 vbta; 	//vertex bitangent
uniform mat4 P, V, M, VM;

//todo: add as uniform...
const float C = 0.1;
const float far = 100000000.0;

out vec2 t_eye;
out vec3 p_eye; 
out vec3 n_eye; 

//for normal map
out vec3 ta_eye;
out vec3 bta_eye;
out float logz;

void main () { 
	p_eye = (VM * vp).xyz; 
	
	n_eye = (VM * vec4 (vn, 0.0)).xyz;
	ta_eye = (VM * vec4 (vta, 0.0)).xyz; 
	bta_eye = (VM * vec4 (vbta, 0.0)).xyz; 


/*
   mat3 norm = mat3(VM);

	n_eye = normalize(((norm * vn) + 1.0) * 0.5) ; 
	ta_eye = norm * vta;
	bta_eye = norm * vbta;

*/

	//n_eye = vn; 
   //ta_eye = vta;
	//bta_eye = vbta;

	t_eye = vt; 
	gl_Position = P * vec4 (p_eye, 1.0); 

   const float FC = 1.0/log(far*C + 1); 
    //logz = gl_Position.w*C + 1;  //version with fragment code 
    logz = log(gl_Position.w*C + 1)*FC;
    gl_Position.z = (2*logz - 1)*gl_Position.w;
}	