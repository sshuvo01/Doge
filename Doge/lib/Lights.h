#ifndef _DOGE_LIGHTS_H_
#define _DOGE_LIGHTS_H_
#include "Core.h"
#include "Shader.h"
#include "Framebuffer.h"
#include <glm/matrix.hpp>

namespace doge
{
	enum class LightType
	{
		POINT, 
		DIRECTIONAL
	};

	class Light
	{
	public:
		NOCOPYNOASSIGN(Light);
		Light() = delete;
		Light(const glm::vec3& pos, const glm::vec3& color, const LightType& type);
		virtual ~Light();
		inline void SetColor(const glm::vec3& color) { m_Color = color; }
		inline const glm::vec3& GetColor() const { return m_Color; }
		inline const LightType& GetType() const { return m_Type; }
		inline void TurnOnShadow() { m_CastShadow = true; }
		inline void TurnOffShadow() { m_CastShadow = false; }
		inline const glm::vec3& GetPosition() const { return m_Position; }
		virtual void SetShaderUniforms() const = 0;
	private:

	protected:
		LightType    m_Type;
		glm::vec3    m_Color;
		bool         m_CastShadow = true;
		glm::vec3    m_Position; 
		Shader*      m_LightShader = nullptr;
	};

	
	// directional light
	class DirectionalLight : public Light
	{
	public:
		NOCOPYNOASSIGN(DirectionalLight);
		DirectionalLight() = delete;
		DirectionalLight(const glm::vec3& pos, const glm::vec3& lookatPos, const glm::vec3& color);
		~DirectionalLight();
		inline const glm::vec3& GetDirection() const { return m_Direction; }
		//inline const glm::mat4& GetLightMat() const { return m_LightSpaceMat; }
		inline const glm::vec3& GetLookAtPos() const { return m_LookAtPos; }
		inline uint GetMapWidth() const { ASSERT(m_DepthMap); return m_DepthMap->GetWidth(); }
		inline uint GetMapHeight() const { ASSERT(m_DepthMap); return m_DepthMap->GetHeight(); }
		inline void BindDepthMap() const { ASSERT(m_DepthMap); m_DepthMap->BindFramebuffer(); }
		inline void UnbindDepthMap() const { ASSERT(m_DepthMap); m_DepthMap->UnbindFramebuffer(); }
		inline void BindDepthTexture(uint slot) const { ASSERT(m_DepthMap); m_DepthMap->BindTexture(slot); }
		inline void BindShader() const { ASSERT(m_LightShader); m_LightShader->Bind(); }
		void SetShaderUniforms() const override;
		inline const glm::mat4& GetLightSpaceMat() const { return m_LightSpaceMat; }
	private:
		glm::vec3      m_Direction, m_LookAtPos;
		glm::mat4      m_LightSpaceMat;
		DepthMap*      m_DepthMap = nullptr;
		/*private functions*/
		void SetupLightSpaceMat();
	};


}

#endif // !_DOGE_LIGHTS_H_

