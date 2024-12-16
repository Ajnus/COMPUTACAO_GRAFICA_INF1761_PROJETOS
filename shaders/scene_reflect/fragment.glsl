#version 410

uniform sampler2D decal;

in data {
  vec3 pos;
  vec3 normal;
  vec3 light;
  vec2 texcoord;
} f;

out vec4 color;

void main (void) 
{
color = vec4(0.0f, 0.0f, 0.0f, 0.9f);
//if (color.a < 1.0)
    //color.a = min(1.0, color.a + texture(decal, f.texcoord).r);
}