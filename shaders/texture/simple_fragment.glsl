#version 410

uniform vec4 color;
uniform sampler2D sampler;

in data{
	vec2 texcoord;
} f;

out vec4 outcolor;

void main(void){
	outcolor = color * texture(sampler,f.texcoord);
}
