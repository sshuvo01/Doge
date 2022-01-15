#version 330 core
#define MAX_LIGHT 16
out vec4 FragColor;
in vec2 texCoord;
in vec3 v_Normal;
in vec4 v_LightSpaceFragPos[MAX_LIGHT];

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

uniform PointLight u_PointLights[MAX_LIGHT];
uniform DirLight u_DirLights[MAX_LIGHT];
uniform int u_PointLightsCount;
uniform int u_DirLightsCount;

uniform vec3 color;
uniform sampler2D u_DiffuseMap;

struct TestStruct
{
	vec3 color;
};

uniform TestStruct uni;

vec3 GetDiffuseColor(vec3 texColor)
{
	vec3 totalColor = vec3(0.0f, 0.0f, 0.0f);
	for(int i = 0; i < u_DirLightsCount; i++)
	{
		float diff = max( dot(-u_DirLights[i].direction, v_Normal), 0.0f);
		totalColor += diff * texColor * u_DirLights[i].color;
	}
	//vec4 r = texture(u_DirLights[0].depthMap, vec2(0.0, 0.0));

	return totalColor;
}

float GetDepthMapShadow(int dirLitInd, float bias)
{
	// perform perspective divide
	vec3 projCoords = v_LightSpaceFragPos[dirLitInd].xyz / v_LightSpaceFragPos[dirLitInd].w;
	// transform to [0, 1] range
	projCoords = projCoords * 0.5 + 0.5;

	float closestDepth = texture(u_DirLights[dirLitInd].depthMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	
	if(currentDepth > 1.0)
	{
		return 0.0;
	}
	// PCF
	float shadow = 0.0;
	vec2 texelSIze = 1.0/textureSize(u_DirLights[dirLitInd].depthMap, 0);
	for(int x = -1; x <= 1; x++)
	{
		for(int y = -1; y <= 1; y++)
		{
			vec2 coord = projCoords.xy + vec2(x, y) * texelSIze;
			float pcfDepth = texture(u_DirLights[dirLitInd].depthMap, coord).r;
			shadow += (currentDepth-bias > pcfDepth ? 1.0 : 0.0);
		}
	}

	shadow = shadow / 9.0;
	return shadow;
}

void main()
{
	vec4 t = texture(u_DiffuseMap, texCoord);
	float amb = 0.15f;
	vec3 diffuse = GetDiffuseColor(t.rgb);
	vec3 ambient = amb * t.rgb;
	//FragColor = vec4( u_DirLights[0].color, 1.0f);
	
	//float bias = max(0.05 * (1.0 - dot(-u_DirLights[0].direction, v_Normal)), 0.005);
	float bias = 0.1;
	float shadow = GetDepthMapShadow(0, bias);

	FragColor = vec4( diffuse * (1.0 - shadow) + ambient, 1.0f);
	//FragColor = vec4( shadow, shadow, shadow, 1.0f);
}