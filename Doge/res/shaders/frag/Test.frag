#version 330 core
#define MAX_LIGHT 12
out vec4 FragColor;
/*
in vec2 texCoord;
in vec3 v_Normal;
in vec3 v_FragPosition;
*/
const float PI = 3.14159265359;

in VS2FS
{
	vec2 texCoord;
	vec3 normal;
	vec3 fragPosition;
	vec4 lightSpaceFragPos[MAX_LIGHT];
	vec3 dirLightPosition_ts[MAX_LIGHT]; // ts = tangent space, ws = world space
	vec3 fragPosition_ts;
	vec3 viewPosition_ts;
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
	sampler2D roughnessMap;
	sampler2D metallicMap;
	sampler2D aoMap;
}; 

uniform PointLight u_PointLights[MAX_LIGHT];
uniform DirLight u_DirLights[MAX_LIGHT];
uniform int u_PointLightsCount;
uniform int u_DirLightsCount;
uniform vec3 u_ViewPosition;
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

vec3 GetSpecularColor(vec3 texColor)
{
	vec3 viewDir_ts = normalize(v_IN.viewPosition_ts - v_IN.fragPosition_ts);
	vec3 nmNormal = GetNMNormal();
	vec3 totalColor = vec3(0.0f, 0.0f, 0.0f);

	for(int i = 0; i < u_DirLightsCount; i++)
	{
		vec3 lightDir_ts = normalize(v_IN.dirLightPosition_ts[i] - v_IN.fragPosition_ts);
		vec3 refDir_ts = reflect(-lightDir_ts, nmNormal);
		float spec = max( dot(refDir_ts, viewDir_ts), 0.0f );
		totalColor += spec * texColor * u_DirLights[i].color; 
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

// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
// ----------------------------------------------------------------------------

void main42()
{
	vec4 t = texture(u_Material.diffuseMap, v_IN.texCoord);
	//float mmm = texture(u_Material.aoMap, v_IN.texCoord).r;
	
	float amb = 0.1f;
	vec3 diffuse = GetDiffuseColor(t.rgb);
	//diffuse = GetDiffuseColor(vec3(mmm));
	// specular
	vec3 specular = GetSpecularColor(t.rgb);


	vec3 ambient = amb * (t.rgb);
	//ambient = amb * vec3(mmm);

	float shadow = GetDirLightsShadow();
	FragColor = vec4( (1.0 - shadow) * diffuse + ambient + specular, 1.0);
}

void main()
{
	vec3 albedo     = pow(texture(u_Material.diffuseMap, v_IN.texCoord).rgb, vec3(2.2));
    float metallic  = texture(u_Material.metallicMap, v_IN.texCoord).r;
    float roughness = texture(u_Material.roughnessMap, v_IN.texCoord).r;
    float ao        = texture(u_Material.aoMap, v_IN.texCoord).r;

	vec3 normal_ts = GetNMNormal();
	vec3 viewDir_ts = normalize(v_IN.viewPosition_ts - v_IN.fragPosition_ts);

	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);

	// reflectance equation 
	vec3 Lo = vec3(0.0f);
	for(int i = 0; i < u_DirLightsCount; i++)
	{
		vec3 lightDir_ts = normalize(v_IN.dirLightPosition_ts[i] - v_IN.fragPosition_ts);
		vec3 halfVecDir_ts = normalize(viewDir_ts + lightDir_ts);
		// no attenuation! for now
		vec3 radiance = u_DirLights[i].color;
		// Cook-Torrance BRDF
		float NDF = DistributionGGX(normal_ts, halfVecDir_ts, roughness);
		float G = GeometrySmith(normal_ts, viewDir_ts, lightDir_ts, roughness);
		vec3 F = fresnelSchlick(max(dot(halfVecDir_ts, viewDir_ts), 0.0f), F0);

		vec3 numerator = NDF * G * F;
		float denominator = 4.0f * max(dot(normal_ts, viewDir_ts), 0.0f) * max(dot(normal_ts, lightDir_ts), 0.0f) + 0.0001;
		vec3 specular = numerator / denominator;

		vec3 kS = F;
		vec3 kD = vec3(1.0f) - kS;

		kD *= 1.0f - metallic;
		float NdotL = max(dot(normal_ts, lightDir_ts), 0.0f);
		Lo += (kD * albedo / PI + specular) * radiance * NdotL;
	}

	vec3 ambient = vec3(0.03f) * albedo * ao;
	vec3 color = ambient + Lo;
	// HDR tonemapping
	color = color / (color + vec3(1.0f));
	// gamma correct
	color = pow(color, vec3(1.0f/ 2.2f));

	float shadow = GetDirLightsShadow();

	FragColor = vec4(color*(1.0 - shadow), 1.0f);
}