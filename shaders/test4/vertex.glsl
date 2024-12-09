#version 410

layout (location=0) in vec4 vertex;
layout (location=1) in vec2 texcoord;


out data {
  vec2 texcoord;
} v;

void main (void)
{
  v.texcoord = texcoord;
  gl_Position = vertex;
}

