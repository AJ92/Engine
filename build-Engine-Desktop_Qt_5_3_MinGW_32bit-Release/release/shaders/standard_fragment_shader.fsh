uniform lowp sampler2D sampler1;
varying lowp vec2 texc;
varying lowp float dir;
void main(void)
{
	lowp vec3 color = texture2D(sampler1, texc.st).rgb;
	gl_FragColor = vec4((color*0.1)+(color*dir*0.9),1.0);
}