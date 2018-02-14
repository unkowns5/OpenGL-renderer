#version 330 core

// Interpolated values from the vertex shaders
// e.g.
in vec2 UV;
in vec3 Position_worldspace;
in vec3 EyeDirection_cameraspace;
in vec3 Normal_cameraspace;
in vec3 LightDirection_cameraspace;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform vec4 diffuseColor;
uniform vec4 ambientColor;
uniform vec4 specularColor;
uniform float opacityV;
uniform float Ns;
uniform mat4 MV;
uniform vec3 lightPosWorldspace;
uniform sampler2D myTextureSampler;
//uniform vec3 LightColor;
//uniform float LightPower;


void main(){
	// Material properties
	//TODO: compute light model here
	//vec3 LightColor = vec3(1,1,1);
	//float LightPower = 0.8f;
	//int levels = 5;
	//float scaleFactor = 1.0 / levels;

	// Normal of the computed fragment, in camera space
	vec3 N = normalize( Normal_cameraspace );
	// Direction of the light (from the fragment to the light)
	vec3 L = normalize( LightDirection_cameraspace );
	//Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_cameraspace);
	//Direction in which the triangle reflects the light
	vec3 R = reflect(-L,N);
	vec3 s = normalize(lightPosWorldspace -  Position_worldspace);
	vec3 v = normalize(EyeDirection_cameraspace-Position_worldspace);
	vec3 h = normalize(v+s) ;
	vec3 specularComponent;

	float distance = length(lightPosWorldspace -  Position_worldspace);

	float cosAlpha = clamp(dot(E,h),0,1);
	
	float cosTheta = clamp( dot(N,L), 0, 1);
	
	//float edgeDetection = (dot(v, Normal_cameraspace)>0.35)? 1 : 0;


	// Material properties
	vec3 MaterialDiffuseColor = texture( myTextureSampler, UV ).rgb;
	//float b = texture( myTextureSampler, UV ).b;
	//vec3 MaterialDiffuseColor =vec3(b,b,b);
	vec3 ambientComponent = ambientColor.rgb * MaterialDiffuseColor;
	specularComponent = specularColor.rgb * pow(cosAlpha, Ns);// (distance*distance);
	
	vec3 diffuseComponent =  diffuseColor.rgb* MaterialDiffuseColor *cosTheta ;// (distance*distance);  //   
	color.rgb = diffuseComponent+ specularComponent  + ambientComponent;
	
    //color.rgb = texture( myTextureSampler, UV ).rgb;
    color.a =  opacityV;

    
}
