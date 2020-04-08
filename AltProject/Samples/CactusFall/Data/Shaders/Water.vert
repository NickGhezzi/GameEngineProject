
attribute vec3 a_Position;
attribute vec2 a_UV;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;
uniform vec3 u_CameraPosition;

uniform float u_Time;

varying vec2 v_UV;

void main()
{
    vec4 objectpos = vec4( a_Position, 1.0 );

    objectpos.y += sin( objectpos.x / 5.0 + u_Time ) * 1.0;
    objectpos.y -= sin( objectpos.z / 40.0 + u_Time ) * 2.0;

    vec4 worldpos = u_WorldMatrix * objectpos;
    vec4 viewpos = u_ViewMatrix * worldpos;
    vec4 clippos = u_ProjMatrix * viewpos;

    gl_Position = clippos;

    v_UV = a_UV;
}
