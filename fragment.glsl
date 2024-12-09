#version 410

uniform vec4 color;
uniform sampler2D sampler;

in data{
	vec2 texcoord;
} f;

out vec4 outcolor;

void main(void){
	outcolor = color ;
}


//out vec4 FragColor;
//uniform vec3 color;

//void main()
//{
//    FragColor = vec4(color, 1.0);
//}

