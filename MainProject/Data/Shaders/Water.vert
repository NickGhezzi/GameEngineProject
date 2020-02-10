#version 120

attribute vec3 a_Position;
attribute vec2 a_UV;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

uniform float u_Time;
uniform vec3 u_RippleOrigin;

varying vec2 v_UV;
varying vec3 v_Pos;

void main()
{
    vec4 objectPosition =  vec4(a_Position, 1);
	vec4 worldPosition = u_WorldMatrix * objectPosition;
	vec4 ripple = vec4(u_RippleOrigin, 1);

	float Distance = sqrt(((worldPosition.x - ripple.x) * (worldPosition.x - ripple.x)) - ((worldPosition.z - ripple.z) * (worldPosition.z - ripple.z)));

	//float Distance = sqrt((( objectPosition.x - worldPosition.x) * (objectPosition.x - worldPosition.x)) - ((objectPosition.z - worldPosition.z) * (objectPosition.z - worldPosition.z)));


	worldPosition.y = (1/Distance + 0.1) * sin(u_Time -  Distance );

	//worldPosition.y += 0.5 * sin(objectPosition.x + u_Time);
	//worldPosition.y += 0.5 * sin(objectPosition.z + u_Time);

    vec4 viewPosition = u_ViewMatrix * worldPosition;
	vec4 clipspacePosition = u_ProjectionMatrix * viewPosition;

    gl_Position = clipspacePosition;

    v_UV = a_UV;
	v_Pos = a_Position;
}
