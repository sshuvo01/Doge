#version 330 core
#define MAX_LIGHT 12
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in mat4 aModelInstance;

struct DirLight
{
	vec3       position; // has a position for now!
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


uniform PointLight u_PointLights[MAX_LIGHT];
uniform DirLight u_DirLights[MAX_LIGHT];
uniform int u_PointLightsCount;
uniform int u_DirLightsCount;

out VS2FS
{
	vec2 texCoord;
	vec3 normal;
	vec3 fragPosition;
	vec4 lightSpaceFragPos[MAX_LIGHT];
	vec3 dirLightPosition_ts[MAX_LIGHT]; // ts = tangent space, ws = world space
	vec3 fragPosition_ts;
}v_OUT;

uniform mat4 u_Model, u_View, u_Projection, u_MVP; 

void main()
{
	// light space 
	for(int i = 0; i < u_DirLightsCount; i++)
	{
		//v_LightSpaceFragPos[i] = u_DirLights[i].lightSpaceMat * aModelInstance * vec4(aPos, 1.0);
		v_OUT.lightSpaceFragPos[i] = u_DirLights[i].lightSpaceMat * aModelInstance * vec4(aPos, 1.0);
		//mat3 mat ;
		//v_OUT.dirLightPosition_ts[i] = mat * vec3(1.0, 1.0, 1.0);
	}
	//
	
	//
	mat3 normalMat = mat3(transpose(inverse(aModelInstance)));
	//v_Normal = normalMat * aNormal;
	vec3 T = normalize(normalMat * aTangent);
	vec3 N = normalize(normalMat * aNormal);
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);
	mat3 invTBNMat = transpose(mat3(T, B, N));
	v_OUT.normal = N;

	for(int i = 0; i < u_DirLightsCount; i++)
	{
		v_OUT.dirLightPosition_ts[i] = invTBNMat * u_DirLights[i].position;
	}

	// invTBNMat (world space to tangent space)
	// TBN (tangent space to world space)
	v_OUT.fragPosition = vec3(aModelInstance * vec4(aPos, 1.0)); // fragPosition is in WS after multiplication
	v_OUT.fragPosition_ts = invTBNMat * v_OUT.fragPosition; 
	v_OUT.texCoord = aTexCoord;

    gl_Position = u_Projection * u_View * aModelInstance * vec4(aPos, 1.0);
}