
#define MAX_RIPPLES         10
#define RIPPLE_FADE_TIME    3.0

attribute vec4 a_Position;
attribute vec2 a_UV;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;

uniform float u_Time;
uniform vec2 u_RipplesCenter[MAX_RIPPLES];
uniform float u_RipplesAge[MAX_RIPPLES];

varying vec2 v_UV;
varying vec4 v_ObjectPos;

void main()
{
    vec2 points[6];
    points[0] = vec2( 0.0, 0.0 );
    points[1] = vec2( 3.0, 8.0 );
    points[2] = vec2( -3.0, 8.0 );
    points[3] = vec2( -3.0, 2.0 );
    points[4] = vec2( 3.0, 2.0 );
    points[5] = vec2( 0.0, 5.0 );

    vec4 objectpos = a_Position;

    //objectpos.y += sin( objectpos.x / 5.0 + u_Time ) * 0.1;
    //objectpos.y -= sin( objectpos.z / 40.0 + u_Time ) * 0.2;

    for( int i=0; i<MAX_RIPPLES; i++ )
    {
        float damping = clamp( (RIPPLE_FADE_TIME - u_RipplesAge[i]) / RIPPLE_FADE_TIME, 0.0, 1.0 );
        float spread = clamp( u_RipplesAge[i] / RIPPLE_FADE_TIME, 0.0, 1.0 );

        float dist = distance( u_RipplesCenter[i], a_Position.xz );
        float range = spread * 2.0;
        float rangeperc = 1.0 - dist/range;
        rangeperc = clamp( rangeperc, 0.0, 1.0 );
        objectpos.y += (-sin( dist * 3.0 + u_RipplesAge[i] * -5.0 ) / 4.0) * 2.0 * rangeperc * damping;
    }

    vec4 worldpos = u_WorldMatrix * objectpos;
    vec4 viewpos = u_ViewMatrix * worldpos;
    vec4 clippos = u_ProjMatrix * viewpos;

    gl_Position = clippos;

    v_ObjectPos = objectpos;
    v_UV = a_UV;
}
