#ifndef _DOGE_MATERIAL_H_
#define _DOGE_MATERIAL_H_
#include "Shader.h"
#include "Texture.h"

namespace doge
{
	struct MapFiles
	{
		std::string diffuseMapFilename;
		std::string roghnessMapFilename;
	};


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
	private:
		std::shared_ptr<Shader>     m_Shader;
		std::shared_ptr<Texture>    m_DiffuseMap = nullptr, m_NormalMap = nullptr;
		/*---------------*/
		void Validate() const;
	};
}

#endif // !_DOGE_MATERIAL_H_
