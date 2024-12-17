#version 410

layout(location = 0) in vec4 pos;
layout(location = 1) in vec3 normal;
layout(location = 3) in vec2 texcoord;

uniform vec4 lpos;  // light pos in lighting space
uniform vec4 cpos;  // camera pos in lighting space
uniform mat4 Mv; 
uniform mat4 Mn; 
uniform mat4 Mvp;

out data {
  vec3 normal;
  vec3 view;
  vec3 light;
  //vec2 texcoord;
} v;

void main (void) 
{
  vec3 p = vec3(Mv*pos);
  if (lpos.w == 0) 
    v.light = normalize(vec3(lpos));
  else 
    v.light = normalize(vec3(lpos)-p); 
  v.view = normalize(vec3(cpos)-p);
  v.normal = normalize(vec3(Mn*vec4(normal,0.0f)));
  //v.texcoord = texcoord;
  gl_Position = Mvp*pos; 
}

