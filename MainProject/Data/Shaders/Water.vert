#version 120

attribute vec3 a_Position;
attribute vec2 a_UV;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

uniform float u_Time;

varying vec2 v_UV;
varying float v_Time;

void main()
{
    vec4 objectPosition =  vec4(a_Position, 1);
	vec4 worldPosition = u_WorldMatrix * objectPosition;

	worldPosition.y += 0.5 * sin(objectPosition.x + u_Time);
	worldPosition.y += 0.5 * sin(objectPosition.z + u_Time);



    vec4 viewPosition = u_ViewMatrix * worldPosition;
	vec4 clipspacePosition = u_ProjectionMatrix * viewPosition;

    gl_Position = clipspacePosition;

    v_UV = a_UV;
}
