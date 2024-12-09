#version 410

in data {
  vec4 color;
} f;

uniform vec4 color;

out vec4 outcolor;

void main (void)
{
  outcolor = f.color;
}
