#version 410

uniform vec4 lamb;
uniform vec4 ldif;
uniform vec4 lspe;

uniform vec4 mamb;
uniform vec4 mdif;
uniform vec4 mspe;
uniform float mshi;

uniform sampler2D decal;

uniform float fdensity;
uniform vec4 fcolor;

in data {
  vec3 pos;
  vec3 normal;
  vec3 light;
  vec2 texcoord;
} f;

out vec4 color;

void main (void) 
{
  vec3 view = normalize(-f.pos);
  vec3 normal = normalize(f.normal);
  vec3 light = normalize(f.light);
  float ndotl = dot(normal,light);
  color = (mamb*lamb + mdif * ldif * max(0,ndotl)) * texture(decal,f.texcoord); 
  if (ndotl > 0) {
    vec3 refl = normalize(reflect(-light,normal));
    color += mspe * lspe * pow(max(0,dot(refl,view)),mshi);
  } 
  //float fog = exp(-pow(fdensity * length(f.pos.z), 2.0));
  float fog = exp(-pow(fdensity * (-f.pos.z), 2));
  color = fog * color + (1 - fog) * fcolor;
}



