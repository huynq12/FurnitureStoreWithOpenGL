#version 400
in vec4 vPosition;
in vec3 vNormal;
in vec4 vColor;

out vec4 color;

uniform vec4 ambientObject, diffuseObject, specularObject;
uniform vec4 LightPosition;
uniform float Shininess;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
void main()
{
	// Transform vertex position into eye coordinates
	vec3 pos = (View * Model * vPosition).xyz;
	vec3 L = normalize( LightPosition.xyz - pos );
	vec3 E = normalize( -pos );
	//(r.v) = (n.h)
	vec3 H = normalize( L + E );

	// Transform vertex normal into eye coordinates
	vec3 N = normalize( View * Model *vec4(vNormal, 0.0) ).xyz;

	// Compute terms in the illumination equation
	vec4 ambient = ambientObject;
	float Kd = max( dot(L, N), 0.0 );
	vec4 diffuse = Kd * diffuseObject;
	float Ks = pow( max(dot(N, H), 0.0), Shininess );
	vec4 specular = Ks * specularObject;
	if( dot(L, N) < 0.0 ) specular = vec4(0.0, 0.0, 0.0, 1.0);
	gl_Position = Projection * View * Model * vPosition / vPosition.w;
	color = ambient + diffuse + specular;
	color.a = 1.0;
	//color = vColor;
}//