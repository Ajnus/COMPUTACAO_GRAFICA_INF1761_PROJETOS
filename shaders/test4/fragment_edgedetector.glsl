#version 410

uniform sampler2D image;

const float S = 20;
const vec3 L = vec3(0.30,0.59,0.11);

#define N 3
const float K[N*N] = float[](
  0.0,-1.0, 0.0,
 -1.0, 4.0,-1.0,
  0.0,-1.0, 0.0
);

in data {
  vec2 texcoord;
} f;

out vec4 outcolor;

float kernel (int i, int j)
{
  return K[N*i+j];
}

void main (void)
{
  float l = 0;
  for (int i=-1; i<=1; ++i) {
    for (int j=-1; j<=1; ++j) {
      vec3 texel = vec3(texture(image,f.texcoord + i*dFdx(f.texcoord) + j*dFdy(f.texcoord)));
      l += kernel(i+1,j+1) * dot(L,texel);
    }
  } 
  outcolor = vec4(S*l,S*l,S*l,1);
}
