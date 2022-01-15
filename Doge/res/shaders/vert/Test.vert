#version 330 core
#define MAX_LIGHT 16
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 aModelInstance;

struct DirLight
{
	vec3       color;
	vec3       direction; // points away from the light like this: o ---->
	bool       isActive;
	bool       castShadow;
	sampler2D  depthMap;
	mat4       lightSpaceMat;
};

struct PointLight
{ 
	vec3 color;
	vec3 position; // position for point light 
	bool hasAtten; // enable attenuation 
	bool isActive;
};

struct TestStruct
{
	vec3 color;
};

uniform TestStruct uni;

uniform PointLight u_PointLights[MAX_LIGHT];
uniform DirLight u_DirLights[MAX_LIGHT];
uniform int u_PointLightsCount;
uniform int u_DirLightsCount;

uniform vec3 color;

out vec2 texCoord;
out vec3 v_Normal;
out vec4 v_LightSpaceFragPos[MAX_LIGHT];

uniform mat4 u_Model, u_View, u_Projection, u_MVP; 

void main()
{
	// light space 
	for(int i = 0; i < u_DirLightsCount; i++)
	{
		v_LightSpaceFragPos[i] = u_DirLights[i].lightSpaceMat * aModelInstance * vec4(aPos, 1.0);
	}
	//


	v_Normal = mat3(transpose(inverse(aModelInstance))) * aNormal;
	texCoord = aTexCoord;
    gl_Position = u_Projection * u_View * aModelInstance * vec4(aPos, 1.0);
}