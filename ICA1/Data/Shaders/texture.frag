#version 120

uniform sampler2D u_Texture;

varying vec4 v_Color;
varying vec3 v_Normal;
varying vec2 v_UV;

void main()
{
    gl_FragColor = texture2D( u_Texture, v_UV );
	//gl_FragColor = vec4(v_Normal, 1);
}