#version 120

attribute vec3 a_Position;
attribute vec2 a_UV;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

uniform float u_Time;
uniform vec3 u_RippleOrigin;

varying vec2 v_UV;
varying float v_Pos;

void main()
{
    vec4 objectPosition =  vec4(a_Position, 1);
	vec4 worldPosition = u_WorldMatrix * objectPosition;
	vec4 ripple = vec4(u_RippleOrigin, 1);

	float Distance = sqrt(((objectPosition.x - ripple.x) * (objectPosition.x - ripple.x)) + ((objectPosition.z - ripple.z) * (objectPosition.z - ripple.z)));
	worldPosition.y =  (5.0/(Distance + 0.1)) * sin(u_Time -  Distance);

	//worldPosition.y += 0.1 * sin(objectPosition.x + u_Time);
	//worldPosition.y += 0.2 * sin(objectPosition.z + u_Time);

    vec4 viewPosition = u_ViewMatrix * worldPosition;
	vec4 clipspacePosition = u_ProjectionMatrix * viewPosition;

    gl_Position = clipspacePosition;

    v_UV = a_UV;
	v_Pos = worldPosition.y * 0.1;
}
