#include "Material.h"

namespace doge
{
	Material::Material()
	{
	}
	
	Material::~Material()
	{
	}

	void Material::SetMaterialUniforms() const
	{
		Validate();
		ShaderSpec ss = m_Shader->GetShaderSpec();
		m_DiffuseMap->Bind(0);
		m_Shader->SetUniform1i(ss.diffuseMapName, 0);
	}

	void Material::Validate() const
	{
		if (!m_Shader)
		{
			spdlog::error("Material is missing shader!");
			ASSERT(false);
			return;
		}
	}
}