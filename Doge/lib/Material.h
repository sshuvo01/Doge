#ifndef _DOGE_MATERIAL_H_
#define _DOGE_MATERIAL_H_
#include "Shader.h"
#include "Texture.h"

namespace doge
{
	class Material
	{
	public:
		Material();
		~Material();

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Texture> m_DiffuseMap;
		void SetMaterialUniforms() const;
	private:
		void Validate() const;
	};
}

#endif // !_DOGE_MATERIAL_H_
