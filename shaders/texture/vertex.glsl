#version 410

layout(location = 0) in vec4 pos;
layout(location = 1) in vec3 normal;
layout(location = 3) in vec2 texcoord;

uniform vec4 lpos;  // light pos in eye space
uniform mat4 Mv; 
uniform mat4 Mn; 
uniform mat4 Mvp;

out data {
  vec3 pos;
  vec3 normal;
  vec3 light;
  vec2 texcoord;
} v;

void main (void) 
{
  v.pos = vec3(Mv*pos);
  if (lpos.w == 0) 
    v.light = normalize(vec3(lpos));
  else 
    v.light = normalize(vec3(lpos)-v.pos); 
  v.normal = normalize(vec3(Mn*vec4(normal,0.0f)));
  v.texcoord = texcoord;
  gl_Position = Mvp*pos; 
}

