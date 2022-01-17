#version 330 core
#define MAX_LIGHT 12
out vec4 FragColor;
/*
in vec2 texCoord;
in vec3 v_Normal;
in vec3 v_FragPosition;
*/
in VS2FS
{
	vec2 texCoord;
	vec3 normal;
	vec3 fragPosition;
	vec4 lightSpaceFragPos[MAX_LIGHT];
	vec3 dirLightPosition_ts[MAX_LIGHT]; // ts = tangent space, ws = world space
	vec3 fragPosition_ts;
}v_IN;


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

struct Material 
{
    sampler2D diffuseMap;
	sampler2D normalMap;
}; 

uniform PointLight u_PointLights[MAX_LIGHT];
uniform DirLight u_DirLights[MAX_LIGHT];
uniform int u_PointLightsCount;
uniform int u_DirLightsCount;
uniform Material u_Material;

//uniform sampler2D u_DiffuseMap;

vec3 GetNMNormal()
{
	vec3 normal = texture(u_Material.normalMap, v_IN.texCoord).rgb;
	return normalize(normal * 2.0 - 1.0);
}

float GetDepthMapShadow(int dirLitInd, float bias)
{
	float minBias = 0.006;
	float biasMult = 0.05;

	// perform perspective divide
	vec3 projCoords = v_IN.lightSpaceFragPos[dirLitInd].xyz / v_IN.lightSpaceFragPos[dirLitInd].w;
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

vec3 GetDiffuseColor(vec3 texColor)
{
	vec3 nmNormal = GetNMNormal();

	vec3 totalColor = vec3(0.0f, 0.0f, 0.0f);
	for(int i = 0; i < u_DirLightsCount; i++)
	{
		//vec3 lightDir = normalize(u_DirLights[i].position - v_FragPosition); 
		vec3 lightDir = normalize(u_DirLights[i].position - v_IN.fragPosition); 

		vec3 lightDir_ts = normalize(v_IN.dirLightPosition_ts[i] - v_IN.fragPosition_ts);

		//float diff = max(dot(lightDir, v_Normal), 0.0f); // lambertian 
		//float diff = max(dot(lightDir, v_IN.normal), 0.0f); // lambertian 
		float diff = max(dot(lightDir_ts, nmNormal), 0.0f); // lambertian 

		totalColor += diff * texColor * u_DirLights[i].color;
	}

	return totalColor;
}

float GetDirLightsShadow()
{
	float shadow = 0.0;
	float minBias = 0.006;
	float biasMult = 0.05;
	for(int i = 0; i < u_DirLightsCount; i++)
	{
		//vec3 lightDir = normalize(u_DirLights[i].position - v_FragPosition);
		vec3 lightDir = normalize(u_DirLights[i].position - v_IN.fragPosition);

		//float bias = max(biasMult * (1.0 - dot(lightDir, v_Normal)), minBias);
		float bias = max(biasMult * (1.0 - dot(lightDir, v_IN.normal)), minBias);
		
		shadow += GetDepthMapShadow(i, bias);
	}

	return clamp(shadow, 0.0, 1.0);
}

void main()
{
	//vec4 t = texture(u_DiffuseMap, texCoord);
	vec4 t = texture(u_Material.diffuseMap, v_IN.texCoord);
	//vec4 tnormal = texture(u_Material.normalMap, v_IN.texCoord);

	float amb = 0.2f;
	vec3 diffuse = GetDiffuseColor(t.rgb);
	vec3 ambient = amb * t.rgb;
	//FragColor = vec4( u_DirLights[0].color, 1.0f);
	

	//float bias = max(0.05 * (1.0 - dot(-u_DirLights[0].direction, v_Normal)), 0.005);
	
	float shadow = GetDirLightsShadow();
	
	//shadow += GetDepthMapShadow(0, bias);
	//shadow += GetDepthMapShadow(1, bias);
	
	FragColor = vec4( diffuse * (1.0 - shadow) + ambient, 1.0 );
	//FragColor = vec4(shadow, shadow, shadow, 1.0);
	//FragColor = vec4(diffuse , 1.0f);
}