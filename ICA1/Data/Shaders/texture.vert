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

void main()
{
    vec4 pos = vec4( a_Position, 1 );
    pos = u_WorldMat * pos;
    pos = u_ViewMat * pos;
    pos = u_ProjMat * pos;

    gl_Position = pos;

    v_UV = a_UV;
	v_Color = a_Color;
	v_Normal = a_Normal;
}
