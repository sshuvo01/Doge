#include "Lights.h"
#include <glm/gtc/matrix_transform.hpp>

namespace doge
{
	Light::Light(const glm::vec3& pos, const glm::vec3& color, const LightType& type)
		:m_CastShadow{ true }, m_Position{ pos }, m_Color{ color }, m_Type{ type }
	{
		spdlog::debug("Constructed light. CastShadow: {}, Position: [{}, {}, {}] ", m_CastShadow, m_Position.x, m_Position.y, m_Position.z);
	}
	
	Light::~Light()
	{
		DELETE(m_LightShader);
	}

	// 
	DirectionalLight::DirectionalLight(const glm::vec3& pos, const glm::vec3& lookatPos, const glm::vec3& color)
		: Light{ pos, color, LightType::DIRECTIONAL }, m_LookAtPos{ lookatPos }
	{
		ASSERT(m_LookAtPos != m_Position);

		m_Direction = glm::normalize(m_LookAtPos - m_Position); // direction points away from the light
		SetupLightSpaceMat();
		m_LightShader = new Shader{ "res/shaders/vert/DepthMap.vert", "res/shaders/frag/DepthMap.frag" };		
		spdlog::debug("Constructed directional light, direction: [{}, {}, {}], color: [{}, {}, {}]", 
			m_Direction.x, m_Direction.y, m_Direction.z, m_Color.r, m_Color.g, m_Color.b);
		//spdlog::debug("Directional light position: [{}, {}, {}]", m_Position.x, m_Position.y, m_Position.z);

		m_DepthMap = new DepthMap{1024, 1024};
	}

	DirectionalLight::~DirectionalLight()
	{
		DELETE(m_DepthMap);
	}

	void DirectionalLight::SetShaderUniforms() const
	{
		ASSERT(m_LightShader);
		m_LightShader->SetUniformMatrix4f("u_LightSpaceMat", m_LightSpaceMat);
	}

	void DirectionalLight::SetupLightSpaceMat()
	{
		float nearPlane = 1.0f, farPlane = 12.5f;
		glm::mat4 lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, nearPlane, farPlane);
		glm::mat4 lightView = glm::lookAt(m_Position, m_LookAtPos, glm::vec3(0.0f, 1.0f, 0.0f));

		m_LightSpaceMat = lightProjection * lightView;
	}
}