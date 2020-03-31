#version 120

attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;
attribute vec3 a_Normal;

uniform mat4 u_WorldMat;
uniform mat4 u_ViewMat;
uniform mat4 u_ProjMat;

varying vec2 v_UV;
varying vec4 v_Color;
varying vec3 v_Normal;
varying vec3 v_WorldSpacePosition;

void main()
{
    vec4 objectSpacePos = vec4( a_Position, 1 );
    vec4 worldSpacePos = u_WorldMat * objectSpacePos;
    vec4 viewSpacePos = u_ViewMat * worldSpacePos;
    vec4 clipSpacePos = u_ProjMat * viewSpacePos;

    gl_Position = clipSpacePos;

    v_UV = a_UV;
	v_Color = a_Color;
	v_Normal = (u_WorldMat * vec4(a_Normal, 0)).xyz;
    //v_Normal = (u_NormalMat * vec4(a_Normal, 0)).xyz;
    v_WorldSpacePosition = worldSpacePos.xyz;
}
