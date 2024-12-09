#version 410

layout (location=0) in vec4 vertex;
layout (location=1) in vec4 icolor;


out data {
  vec4 color;
} v;

uniform mat4 mvp;

void main (void)
{
  v.color = icolor;
  gl_Position = mvp * vertex;
}

