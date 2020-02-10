#version 120

uniform sampler2D u_Texture;
uniform float u_Time;

varying vec4 v_Color;
varying vec2 v_UV;
varying float v_Pos;

void main()
{
	vec4 tex = vec4(0, 0, 0.7, 1);
	vec4 tex2 = vec4(0.5, 0.5, 0.5, 1);

	vec2 uv = (vec2(u_Time , u_Time) * 0.01) + v_UV;
	vec2 uv1 = (vec2(u_Time , u_Time) * 0.007) + (v_UV + vec2(0.09, 0.2));

	tex.b += v_Pos;
	gl_FragColor = tex;

	gl_FragColor = tex2 * texture2D( u_Texture, uv1 );
    gl_FragColor += texture2D( u_Texture, uv ) + tex;

	
	
}