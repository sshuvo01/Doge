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
		//m_Shader->SetUniform3f("uni.color", { 1.0f, 1.0f, 0.0f });
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