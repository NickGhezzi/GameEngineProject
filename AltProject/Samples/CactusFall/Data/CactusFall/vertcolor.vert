
attribute vec4 a_Position;
attribute vec4 a_Color;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;

varying vec4 v_Color;

void main()
{
	vec4 objectpos = a_Position;

	vec4 worldpos = u_WorldMatrix * objectpos;
	vec4 viewpos = u_ViewMatrix * worldpos;
	vec4 clippos = u_ProjMatrix * viewpos;

	gl_Position = clippos;

	v_Color = a_Color;
}
