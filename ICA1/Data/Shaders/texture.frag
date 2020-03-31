#version 120

uniform sampler2D u_Texture;
uniform vec3 u_LightColor;
uniform vec3 u_LightPos;
uniform vec3 u_CameraPos;


varying vec4 v_Color;
varying vec3 v_Normal;
varying vec2 v_UV;
varying vec3 v_WorldSpacePosition;


void main()
{
	float u_LightRadius = 10;
	//vec3 u_LightPos =  vec3(0,2,0); //TODO: Make this a uniform
	vec4 materialColor = texture2D(u_Texture, v_UV);
	
	vec3 unnormalizedDirTowardsLight = u_LightPos - v_WorldSpacePosition;
	float dist = length( unnormalizedDirTowardsLight );
	vec3 dirTowardsLight = normalize( unnormalizedDirTowardsLight );

	vec3 normal = normalize(v_Normal);
	float diffusePerc = dot(dirTowardsLight, normal);
	//diffusePerc = diffusePerc / dist;
	//diffusePerc = clamp( diffusePerc ,0 ,1 ); 
	vec3 lightDirShortened = unnormalizedDirTowardsLight / u_LightRadius;
	float attenuation = max( 0.0, 1.0 - dot( lightDirShortened, lightDirShortened ) );
	diffusePerc *= attenuation;

	//specular
	vec3 dirTowardsCamera = normalize(u_CameraPos - v_WorldSpacePosition);
	vec3 halfVector = normalize(dirTowardsCamera + dirTowardsCamera);
	float specularPerc = dot(normal, halfVector); 
	specularPerc = pow(specularPerc, 50); //50 is shinyness. add u_ShineAmount
	specularPerc *= attenuation;


	vec3 diffuseColor = materialColor.rgb * u_LightColor * diffusePerc;
	vec3 specularColor = u_LightColor * specularPerc;

	gl_FragColor = vec4(diffuseColor + specularColor, materialColor.a);
    //gl_FragColor = texture2D( u_Texture, v_UV );
	//gl_FragColor = vec4(v_Normal, 1);
	//gl_FragColor = vec4(v_WorldSpacePosition,1 );
}