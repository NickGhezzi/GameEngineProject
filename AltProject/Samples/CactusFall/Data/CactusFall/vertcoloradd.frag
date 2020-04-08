
uniform vec4 u_AddColor;

varying vec4 v_Color;

void main()
{
	gl_FragColor = v_Color + u_AddColor;
}
