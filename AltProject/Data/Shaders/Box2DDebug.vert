#version 120

attribute vec3 a_Position;

uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;

void main()
{
    vec4 worldpos = vec4( a_Position, 1 );
    vec4 viewpos = u_ViewMatrix * worldpos;
    vec4 clippos = u_ProjMatrix * viewpos;

    gl_Position = clippos;
}
