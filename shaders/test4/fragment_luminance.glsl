#version 410

uniform sampler2D image;

const vec3 L = vec3(0.30,0.59,0.11);

in data {
  vec2 texcoord;
} f;

out vec4 outcolor;

void main (void)
{
  float l = dot(L,vec3(texture(image,f.texcoord)));
  outcolor = vec4(l,l,l,1);
}
