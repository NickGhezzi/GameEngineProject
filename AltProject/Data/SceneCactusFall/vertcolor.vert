#version 120

attribute vec3 a_Position;
attribute vec4 a_Color;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

varying vec4 v_Color;

void main()
{
	vec4 objectpos = vec4( a_Position, 1.0 );
	vec4 worldpos = u_WorldMatrix * objectpos;
	vec4 viewpos = u_ViewMatrix * worldpos;
	vec4 clippos = u_ProjectionMatrix * viewpos;

	gl_Position = clippos;

	v_Color = a_Color;
}
