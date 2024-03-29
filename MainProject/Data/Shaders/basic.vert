#version 120

attribute vec2 a_Position;
attribute vec4 a_Color;

uniform mat4 u_WorldMatrix;
uniform vec2 u_CameraTranslation;
uniform vec2 u_ProjectionScale;

varying vec4 v_Color;

void main()
{
    vec4 objectPosition = vec4( a_Position, 0, 1 );

	vec4 worldPosition = u_WorldMatrix * objectPosition;

    vec4 viewPosition = worldPosition + vec4( u_CameraTranslation, 0, 0 );
    
	vec4 clipspacePosition = viewPosition * vec4(u_ProjectionScale, 1, 1);

    gl_Position = clipspacePosition;

    v_Color = a_Color;
}
