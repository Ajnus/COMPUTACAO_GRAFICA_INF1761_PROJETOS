#version 410

layout(location = 0) in vec4 pos;
layout(location = 1) in vec3 normal;
layout(location = 3) in vec2 texcoord;

out data {
  vec3 pos;
  vec3 normal;
  vec3 light;
  vec2 texcoord;
} f;

uniform mat4 Mv;
uniform mat4 Mvp;
uniform vec4 clipPlane;
out float gl_ClipDistance[1];

void main (void) 
{
  vec3 p = vec3(Mv*pos);
  vec4 p2 = Mv*pos;
  gl_Position = Mvp*pos;
  gl_ClipDistance[0] = dot(clipPlane,p2); 
}

