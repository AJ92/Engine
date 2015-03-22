#version 400
uniform sampler2D l_tex;
uniform sampler2D p_tex;
uniform vec2 win_size;
uniform int frame_switch;
uniform int function;   //0 = fxaa; 1 = noise; 2 = sharpening; 4 = h_blur; 5 = v_blur; 5 = h_blur_lumin; 6 = v_blur_lumin;


//the edge texture
layout( location = 0 ) out vec4 def_e;


//the spread of the edge detection algorithm
//2.5 works well
float fScale = 2.5f;

float GetColorLuminance( vec3 i_vColor )
{
  return dot( i_vColor, vec3( 0.2126f, 0.7152f, 0.0722f ) );
}


//SIMPLE NOISE
float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 343758.5453);
}


//MORE POWERFULL NOISE
vec4 mod289(vec4 x)
{
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 permute(vec4 x)
{
  return mod289(((x*34.0)+1.0)*x);
}

vec4 taylorInvSqrt(vec4 r)
{
  return 1.79284291400159 - 0.85373472095314 * r;
}

vec2 fade(vec2 t) {
  return t*t*t*(t*(t*6.0-15.0)+10.0);
}

// Classic Perlin noise
float cnoise(vec2 P)
{
  vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);
  vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);
  Pi = mod289(Pi); // To avoid truncation effects in permutation
  vec4 ix = Pi.xzxz;
  vec4 iy = Pi.yyww;
  vec4 fx = Pf.xzxz;
  vec4 fy = Pf.yyww;

  vec4 i = permute(permute(ix) + iy);

  vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0 ;
  vec4 gy = abs(gx) - 0.5 ;
  vec4 tx = floor(gx + 0.5);
  gx = gx - tx;

  vec2 g00 = vec2(gx.x,gy.x);
  vec2 g10 = vec2(gx.y,gy.y);
  vec2 g01 = vec2(gx.z,gy.z);
  vec2 g11 = vec2(gx.w,gy.w);

  vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));
  g00 *= norm.x;  
  g01 *= norm.y;  
  g10 *= norm.z;  
  g11 *= norm.w;  

  float n00 = dot(g00, vec2(fx.x, fy.x));
  float n10 = dot(g10, vec2(fx.y, fy.y));
  float n01 = dot(g01, vec2(fx.z, fy.z));
  float n11 = dot(g11, vec2(fx.w, fy.w));

  vec2 fade_xy = fade(Pf.xy);
  vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);
  float n_xy = mix(n_x.x, n_x.y, fade_xy.y);
  return 2.3 * n_xy;
}

// Classic Perlin noise, periodic variant
float pnoise(vec2 P, vec2 rep)
{
  vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);
  vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);
  Pi = mod(Pi, rep.xyxy); // To create noise with explicit period
  Pi = mod289(Pi);        // To avoid truncation effects in permutation
  vec4 ix = Pi.xzxz;
  vec4 iy = Pi.yyww;
  vec4 fx = Pf.xzxz;
  vec4 fy = Pf.yyww;

  vec4 i = permute(permute(ix) + iy);

  vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0 ;
  vec4 gy = abs(gx) - 0.5 ;
  vec4 tx = floor(gx + 0.5);
  gx = gx - tx;

  vec2 g00 = vec2(gx.x,gy.x);
  vec2 g10 = vec2(gx.y,gy.y);
  vec2 g01 = vec2(gx.z,gy.z);
  vec2 g11 = vec2(gx.w,gy.w);

  vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));
  g00 *= norm.x;  
  g01 *= norm.y;  
  g10 *= norm.z;  
  g11 *= norm.w;  

  float n00 = dot(g00, vec2(fx.x, fy.x));
  float n10 = dot(g10, vec2(fx.y, fy.y));
  float n01 = dot(g01, vec2(fx.z, fy.z));
  float n11 = dot(g11, vec2(fx.w, fy.w));

  vec2 fade_xy = fade(Pf.xy);
  vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);
  float n_xy = mix(n_x.x, n_x.y, fade_xy.y);
  return 2.3 * n_xy;
}






#ifndef FXAA_REDUCE_MIN
    #define FXAA_REDUCE_MIN   (1.0/ 128.0)
#endif
#ifndef FXAA_REDUCE_MUL
    #define FXAA_REDUCE_MUL   (1.0 / 8.0)
#endif
#ifndef FXAA_SPAN_MAX
    #define FXAA_SPAN_MAX     8.0
#endif

//optimized version for mobile, where dependent 
//texture reads can be a bottleneck
vec4 fxaa(sampler2D tex, vec2 fragCoord, vec2 resolution) {
    vec4 color;
    
  vec2 inverseVP = 1.0 / resolution.xy;

  vec2 v_rgbNW = (fragCoord + vec2(-1.0, -1.0)) * inverseVP;
  vec2 v_rgbNE = (fragCoord + vec2(1.0, -1.0)) * inverseVP;
  vec2 v_rgbSW = (fragCoord + vec2(-1.0, 1.0)) * inverseVP;
  vec2 v_rgbSE = (fragCoord + vec2(1.0, 1.0)) * inverseVP;
  vec2 v_rgbM = vec2(fragCoord * inverseVP);

  vec3 rgbNW = texture2D(tex, v_rgbNW).xyz;
  vec3 rgbNE = texture2D(tex, v_rgbNE).xyz;
  vec3 rgbSW = texture2D(tex, v_rgbSW).xyz;
  vec3 rgbSE = texture2D(tex, v_rgbSE).xyz;
  vec4 texColor = texture2D(tex, v_rgbM);
  vec3 rgbM  = texColor.xyz;
  vec3 luma = vec3(0.299, 0.587, 0.114);
  float lumaNW = dot(rgbNW, luma);
  float lumaNE = dot(rgbNE, luma);
  float lumaSW = dot(rgbSW, luma);
  float lumaSE = dot(rgbSE, luma);
  float lumaM  = dot(rgbM,  luma);
  float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
  float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));
  
  mediump vec2 dir;
  dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
  dir.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));
  
  float dirReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) *
                        (0.25 * FXAA_REDUCE_MUL), FXAA_REDUCE_MIN);
  
  float rcpDirMin = 1.0 / (min(abs(dir.x), abs(dir.y)) + dirReduce);
  dir = min(vec2(FXAA_SPAN_MAX, FXAA_SPAN_MAX),
            max(vec2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX),
            dir * rcpDirMin)) * inverseVP;
  
  vec3 rgbA = 0.5 * (
      texture2D(tex, fragCoord * inverseVP + dir * (1.0 / 3.0 - 0.5)).xyz +
      texture2D(tex, fragCoord * inverseVP + dir * (2.0 / 3.0 - 0.5)).xyz);
  vec3 rgbB = rgbA * 0.5 + 0.25 * (
      texture2D(tex, fragCoord * inverseVP + dir * -0.5).xyz +
      texture2D(tex, fragCoord * inverseVP + dir * 0.5).xyz);

  float lumaB = dot(rgbB, luma);
  if ((lumaB < lumaMin) || (lumaB > lumaMax))
      color = vec4(rgbA, texColor.a);
  else
      color = vec4(rgbB, texColor.a);
  return color;
}



//sharpen filter
vec4 sharpen(sampler2D tex, vec2 fragCoord, vec2 resolution, float percentage){
  float kernel[9];
  vec2 offset[9];
  float step_w = 1.0/resolution.x;
  float step_h = 1.0/resolution.y;

  //output
  vec4 color = vec4(0.0);


  offset[0] = vec2(-step_w, -step_h);
  offset[1] = vec2(0.0, -step_h);
  offset[2] = vec2(step_w, -step_h);
  offset[3] = vec2(-step_w, 0.0);
  offset[4] = vec2(0.0, 0.0);
  offset[5] = vec2(step_w, 0.0);
  offset[6] = vec2(-step_w, step_h);
  offset[7] = vec2(0.0, step_h);
  offset[8] = vec2(step_w, step_h);


  /* SHARPEN KERNEL
   0 -1  0
  -1  5 -1
   0 -1  0
  */

  kernel[0] = 0.;
  kernel[1] = -1.;
  kernel[2] = 0.;
  kernel[3] = -1.;
  kernel[4] = 5.;
  kernel[5] = -1.;
  kernel[6] = 0.;
  kernel[7] = -1.;
  kernel[8] = 0.;

  int i;

  vec4 original_color = texture2D(tex, fragCoord);

  for (i = 0; i < 9; i++) {
          vec4 color_value = texture2D(tex, fragCoord + offset[i]);
          color += color_value * kernel[i];
  }
  return original_color * (1.0 - percentage) + color * percentage;
}



vec4 fastGaussianBlurHorizontal(sampler2D tex, vec2 fragCoord, vec2 resolution){

  float step_w = 1.0/resolution.x;
  float step_h = 1.0/resolution.y;

  //output
  vec4 color = vec4(0.0);

  //horizontal blur
  vec2 h_blurTexCoords[14];

  h_blurTexCoords[ 0] = fragCoord + vec2(-13.5 * step_w, 0.0);
  h_blurTexCoords[ 1] = fragCoord + vec2(-11.5 * step_w, 0.0);
  h_blurTexCoords[ 2] = fragCoord + vec2(-9.5 * step_w, 0.0);
  h_blurTexCoords[ 3] = fragCoord + vec2(-7.5 * step_w, 0.0);
  h_blurTexCoords[ 4] = fragCoord + vec2(-5.5 * step_w, 0.0);
  h_blurTexCoords[ 5] = fragCoord + vec2(-3.5 * step_w, 0.0);
  h_blurTexCoords[ 6] = fragCoord + vec2(-1.5 * step_w, 0.0);
  h_blurTexCoords[ 7] = fragCoord + vec2( 1.5 * step_w, 0.0);
  h_blurTexCoords[ 8] = fragCoord + vec2( 3.5 * step_w, 0.0);
  h_blurTexCoords[ 9] = fragCoord + vec2( 5.5 * step_w, 0.0);
  h_blurTexCoords[10] = fragCoord + vec2( 7.5 * step_w, 0.0);
  h_blurTexCoords[11] = fragCoord + vec2( 9.5 * step_w, 0.0);
  h_blurTexCoords[12] = fragCoord + vec2( 11.5 * step_w, 0.0);
  h_blurTexCoords[13] = fragCoord + vec2( 13.5 * step_w, 0.0);

  vec4 h_blur = vec4(0.0);
  h_blur += texture2D(tex, h_blurTexCoords[ 0]) *0.0044299121055113265;
  h_blur += texture2D(tex, h_blurTexCoords[ 1]) *0.00895781211794;
  h_blur += texture2D(tex, h_blurTexCoords[ 2]) *0.0215963866053;
  h_blur += texture2D(tex, h_blurTexCoords[ 3]) *0.0443683338718;
  h_blur += texture2D(tex, h_blurTexCoords[ 4]) *0.0776744219933;
  h_blur += texture2D(tex, h_blurTexCoords[ 5]) *0.115876621105;
  h_blur += texture2D(tex, h_blurTexCoords[ 6]) *0.147308056121;
  h_blur += texture2D(tex, fragCoord          )   *0.159576912161;
  h_blur += texture2D(tex, h_blurTexCoords[ 7]) *0.147308056121;
  h_blur += texture2D(tex, h_blurTexCoords[ 8]) *0.115876621105;
  h_blur += texture2D(tex, h_blurTexCoords[ 9]) *0.0776744219933;
  h_blur += texture2D(tex, h_blurTexCoords[10]) *0.0443683338718;
  h_blur += texture2D(tex, h_blurTexCoords[11]) *0.0215963866053;
  h_blur += texture2D(tex, h_blurTexCoords[12]) *0.00895781211794;
  h_blur += texture2D(tex, h_blurTexCoords[13]) *0.0044299121055113265;


  color = h_blur;

  return color;
}


vec4 fastGaussianBlurVertical(sampler2D tex, vec2 fragCoord, vec2 resolution){

  float step_w = 1.0/resolution.x;
  float step_h = 1.0/resolution.y;

  //output
  vec4 color = vec4(0.0);


  //vertical blur
  vec2 v_blurTexCoords[14];

  v_blurTexCoords[ 0] = fragCoord + vec2(0.0, -13.5 * step_h);
  v_blurTexCoords[ 1] = fragCoord + vec2(0.0, -11.5 * step_h);
  v_blurTexCoords[ 2] = fragCoord + vec2(0.0, -9.5 * step_h);
  v_blurTexCoords[ 3] = fragCoord + vec2(0.0, -7.5 * step_h);
  v_blurTexCoords[ 4] = fragCoord + vec2(0.0, -5.5 * step_h);
  v_blurTexCoords[ 5] = fragCoord + vec2(0.0, -3.5 * step_h);
  v_blurTexCoords[ 6] = fragCoord + vec2(0.0, -1.5 * step_h);
  v_blurTexCoords[ 7] = fragCoord + vec2(0.0,  1.5 * step_h);
  v_blurTexCoords[ 8] = fragCoord + vec2(0.0,  3.5 * step_h);
  v_blurTexCoords[ 9] = fragCoord + vec2(0.0,  5.5 * step_h);
  v_blurTexCoords[10] = fragCoord + vec2(0.0,  7.5 * step_h);
  v_blurTexCoords[11] = fragCoord + vec2(0.0,  9.5 * step_h);
  v_blurTexCoords[12] = fragCoord + vec2(0.0,  11.5 * step_h);
  v_blurTexCoords[13] = fragCoord + vec2(0.0,  13.5 * step_h);


  vec4 v_blur = vec4(0.0);
  v_blur += texture2D(tex, v_blurTexCoords[ 0]) *0.0044299121055113265;
  v_blur += texture2D(tex, v_blurTexCoords[ 1]) *0.00895781211794;
  v_blur += texture2D(tex, v_blurTexCoords[ 2]) *0.0215963866053;
  v_blur += texture2D(tex, v_blurTexCoords[ 3]) *0.0443683338718;
  v_blur += texture2D(tex, v_blurTexCoords[ 4]) *0.0776744219933;
  v_blur += texture2D(tex, v_blurTexCoords[ 5]) *0.115876621105;
  v_blur += texture2D(tex, v_blurTexCoords[ 6]) *0.147308056121;
  v_blur += texture2D(tex, fragCoord          )  *0.159576912161;
  v_blur += texture2D(tex, v_blurTexCoords[ 7]) *0.147308056121;
  v_blur += texture2D(tex, v_blurTexCoords[ 8]) *0.115876621105;
  v_blur += texture2D(tex, v_blurTexCoords[ 9]) *0.0776744219933;
  v_blur += texture2D(tex, v_blurTexCoords[10]) *0.0443683338718;
  v_blur += texture2D(tex, v_blurTexCoords[11]) *0.0215963866053;
  v_blur += texture2D(tex, v_blurTexCoords[12]) *0.00895781211794;
  v_blur += texture2D(tex, v_blurTexCoords[13]) *0.0044299121055113265;

  color = v_blur;

  return color;
}




void main () {

  vec2 st;
  st.s = gl_FragCoord.x / win_size.x;
  st.t = gl_FragCoord.y / win_size.y;


/*
  //vec4 p_texel = texture (p_tex, st);
  //fScale = (1.0f + p_texel.z * 0.00001f) * fScale;
  //fScale = rand(vec2(frame_switch * st.s ,frame_switch * st.t)) * 15.0f;

  vec2 vPixelViewport = vec2( 1.0f / win_size.x, 1.0f / win_size.y );



  // Offset coordinates
  vec2 upOffset = vec2( 0.0f , vPixelViewport.y ) * fScale;
  vec2 rightOffset = vec2( vPixelViewport.x, 0.0f ) * fScale;


  float vector1 = 0.0;
  float vector2 = 0.0;


  float topHeight = GetColorLuminance( texture( l_tex, st + upOffset).rgb );
  float bottomHeight = GetColorLuminance( texture( l_tex, st - upOffset).rgb );
  float rightHeight = GetColorLuminance( texture( l_tex, st + rightOffset).rgb );
  float leftHeight = GetColorLuminance( texture( l_tex, st - rightOffset).rgb );
  
  float leftTopHeight = GetColorLuminance( texture( l_tex, st - rightOffset + upOffset).rgb );
  float leftBottomHeight = GetColorLuminance( texture( l_tex, st - rightOffset - upOffset).rgb );
  float rightBottomHeight = GetColorLuminance( texture( l_tex, st + rightOffset + upOffset).rgb );
  float rightTopHeight = GetColorLuminance( texture( l_tex, st + rightOffset - upOffset).rgb );
  
  // Normal map creation
  float sum0 = rightTopHeight+ topHeight + rightBottomHeight;
  float sum1 = leftTopHeight + bottomHeight + leftBottomHeight;
  float sum2 = leftTopHeight + leftHeight + rightTopHeight;
  float sum3 = leftBottomHeight + rightHeight + rightBottomHeight;


  vector1 = (sum1 - sum0);
  vector2 = (sum2 - sum3);

  
  //discard 
  vec3 Scene0 = texture( l_tex, st ).rgb;


  // Put them together and scale.
  vec2 Normal = vec2( vector2, vector1);
  Normal.xy = clamp(Normal,vec2(-1.0,-1.0)*0.4,vec2(1.0,1.0)*0.4); //Prevent over-blurring in high-contrast areas! -venzon
  vec2 final_norm = Normal * vPixelViewport * fScale;  // Increase pixel size to get more blur

  vec3 Scene1 = texture( l_tex, st + final_norm.xy ).rgb;
  vec3 Scene2 = texture( l_tex, st - final_norm.xy ).rgb;
  vec3 Scene3 = texture( l_tex, st + vec2(final_norm.x, -final_norm.y) * 0.5f ).rgb;
  vec3 Scene4 = texture( l_tex, st - vec2(final_norm.x, -final_norm.y) * 0.5f ).rgb;


  //Final color smoothed
  vec3 out_c = (Scene0 + Scene1 + Scene2 + Scene3 + Scene4) * 0.2;
//  if((out_c.r +out_c.g + out_c.b) < 0.00001){
//    discard;
//  }

  //output the corrected color
  //def_e.rgb = out_c;
  //show the normals of the smooth pixels
  //def_e.rgb = normalize( vec3(Normal.x, Normal.y , 1.0f ) * 0.5f + 0.5f);

  //something like a depth value....
  //def_e.rgb = vec3(1.0 + p_texel.z * 0.0001, 1.0 + p_texel.z * 0.0001, 1.0 + p_texel.z * 0.0001);
  
  //vec3 out_c = texture( l_tex, st ).rgb;
*/


  if(function == 0){
    ///////////////////////////////////////////
    //FXAA
    def_e.rgb = fxaa(l_tex,gl_FragCoord.st,win_size).rgb;
    //FXAA END
    //////////////////////////////////////////
    def_e.a = 1.0f;
  }
  if(function == 1){

    vec3 tex_c = texture( l_tex, st).rgb;

    ///////////////////////////////////////////
    //LUMINANCE
    float lumin = clamp(vec3(GetColorLuminance(tex_c)),0.0,1.0);
    ///////////////////////////////////////////


    ///////////////////////////////////////////
    //NOISE
    float noise_value = clamp(rand(vec2(frame_switch * st.s,frame_switch * st.t)),0.0,1.0);
    vec3 out_c_noise = vec3(noise_value);
    //NOISE END
    //////////////////////////////////////////

    
    def_e.rgb = tex_c + ((out_c_noise - 0.5f) * 0.02 * clamp(0.4 - lumin,0.0,1.0));
    def_e.a = 1.0f;
  }

  if(function == 2){
    ///////////////////////////////////////////
    //SHARPEN
    def_e.rgb =  sharpen(l_tex, st, win_size, 0.2).rgb;
    //SHARPEN END
    //////////////////////////////////////////
    def_e.a = 1.0f;
  }

  if(function == 3){
    def_e.rgb = fastGaussianBlurHorizontal(l_tex, st, win_size).rgb;
    def_e.a = 1.0f;
  }

  if(function == 4){
    def_e.rgb = fastGaussianBlurVertical(l_tex, st, win_size).rgb;
    def_e.a = 1.0f;
  }

  if(function == 5){

    vec3 tex_c = texture( l_tex, st).rgb;

    ///////////////////////////////////////////
    //LUMINANCE
    float lumin = clamp(vec3(GetColorLuminance(tex_c)),0.0,1.0);
    ///////////////////////////////////////////


    vec3 blur = fastGaussianBlurHorizontal(l_tex, st, win_size).rgb;
    def_e.rgb = blur;
    def_e.a = 1.0f;
  }



}