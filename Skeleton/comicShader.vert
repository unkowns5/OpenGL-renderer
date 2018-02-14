#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 lightPosWorldspace;

void main(){
	
	// Output position of the vertex, in clip space : MVP * position
	vec3 v = vertexPosition_modelspace;
	//flatten the z coord of all vertices
	v.z = v.z/50;
	gl_Position =  MVP * vec4(v,1);

	Position_worldspace =(M * vec4(vertexPosition_modelspace,1)).xyz;
	vec3 vertexPosition_cameraspace = (V * M * vec4(vertexPosition_modelspace,1)).xyz;
	vec3 lightPosWorldspace = (V * vec4(lightPosWorldspace,1)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	LightDirection_cameraspace = lightPosWorldspace +
		EyeDirection_cameraspace;

	Normal_cameraspace = ( V * M * vec4(vertexNormal_modelspace,0)).xyz;
	
	UV = vertexUV;
}

