#version 410
#define N 2

uniform vec4 lamb;
uniform vec4 ldif;
uniform vec4 lspe;

uniform vec4 mamb;
uniform vec4 mdif;
uniform vec4 mspe;
uniform float mshi;
uniform float mopacity;

uniform sampler2D decal;

in data {
  vec3 normal;
  vec3 view;
  vec3 light;
  vec2 texcoord;
} f;

out vec4 color;

uniform vec4 planecolor;
uniform vec4 clipPlane;

void main (void) 
{
  vec3 normal = normalize(gl_FrontFacing ? f.normal : -f.normal);
  vec3 light = normalize(f.light);
  vec3 view = normalize(f.view);
  float ndotl = dot(normal,light);

  if (gl_FrontFacing)
    color = mamb*lamb + mdif * ldif * max(0,ndotl) * texture(decal,f.texcoord); 
  else
  // color = (planecolor * lamb + planecolor * ldif * max (0, ndotl));
  // vec4(1.0, 1.0, 1.0, 1.0);  
    color = (planecolor + planecolor * max (0, ndotl)); 
    

  if (ndotl > 0) {
    vec3 refl = normalize(reflect(-light,normal));
    color += mspe * lspe * pow(max(0,dot(refl,view)),mshi); 
  }

  color.a = mopacity;
}



