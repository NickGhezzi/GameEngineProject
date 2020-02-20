#version 120

attribute vec3 a_Position;
attribute vec2 a_UV;

uniform mat4 u_WorldMat;
uniform mat4 u_ViewMat;
uniform mat4 u_ProjMat;

varying vec2 v_UV;

void main()
{
    vec4 pos = vec4( a_Position, 1 );
    pos = u_WorldMat * pos;
    pos = u_ViewMat * pos;
    pos = u_ProjMat * pos;

    gl_Position = pos;

    v_UV = a_UV;
}
