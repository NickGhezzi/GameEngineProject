#version 120

attribute vec3 a_Position;
attribute vec2 a_UV;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

varying vec2 v_UV;

void main()
{
    vec4 objectPosition =  vec4(a_Position, 1);
	vec4 worldPosition = u_WorldMatrix * objectPosition;
    vec4 viewPosition = u_ViewMatrix * worldPosition;
	vec4 clipspacePosition = u_ProjectionMatrix * viewPosition;

    gl_Position = clipspacePosition;

    v_UV = a_UV;
}
