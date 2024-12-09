#version 410

layout (location=0) in vec4 vertex;
layout (location=1) in vec4 icolor;

out vec4 color;

void main (void)
{
  color = icolor;
  gl_Position = vertex;
}

