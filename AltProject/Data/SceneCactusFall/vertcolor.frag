#version 120
uniform vec3 u_Color;
varying vec4 v_Color;

void main()
{
vec4 color;

if(u_Color != vec3(0,0,0))
{
	color = vec4 (u_Color, 1);
}
else
{
	color  = v_Color;
}
	gl_FragColor = color;
}
