#version 120

uniform sampler2D u_Texture;

varying vec4 v_Color;
varying vec2 v_UV;
varying float v_Time;

void main()
{

    gl_FragColor = texture2D( u_Texture, v_UV );


}