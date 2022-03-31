#ifndef _DOGE_MATERIAL_H_
#define _DOGE_MATERIAL_H_
#include "Shader.h"
#include "Texture.h"

namespace doge
{
	

	class Material 
	{
	public:
		NOCOPYNOASSIGN(Material);
		Material();
		~Material();
		void SetMaterialUniforms() const;
		inline const std::shared_ptr<Texture>& GetDiffuseMap() const { return m_DiffuseMap; }
		inline const std::shared_ptr<Shader>& GetShader() const { return m_Shader; }
		inline void SetShader(const std::shared_ptr<Shader>& shader) { m_Shader = shader; }
		inline void SetDiffuseMap(const std::shared_ptr<Texture>& diffMap) { m_DiffuseMap = diffMap; }
		inline void SetNormalMap(const std::shared_ptr<Texture>& normalMap) { m_NormalMap = normalMap; }
		inline void SetRoughnessMap(const std::shared_ptr<Texture>& roughnessMap) { m_RoughnessMap = roughnessMap; }
		inline void SetMetallicMap(const std::shared_ptr<Texture>& metallicMap) { m_MetallicMap = metallicMap; }
		inline void SetAmbientOcclusionMap(const std::shared_ptr<Texture>& aoMap) { m_AOMap = aoMap; }
	private:
		std::shared_ptr<Shader>     m_Shader;
		std::shared_ptr<Texture>    m_DiffuseMap = nullptr, m_NormalMap = nullptr, m_RoughnessMap = nullptr, m_MetallicMap = nullptr, m_AOMap = nullptr;
		/*---------------*/
		void Validate() const;
	};
}

#endif // !_DOGE_MATERIAL_H_
