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
		m_Shader->SetUniform1i("u_Material.diffuseMap", 0);
		
		m_NormalMap->Bind(1);
		m_Shader->SetUniformTexture("u_Material.normalMap", 1);
		
		m_RoughnessMap->Bind(2);
		m_Shader->SetUniformTexture("u_Material.roughnessMap", 2);

		m_MetallicMap->Bind(3);
		m_Shader->SetUniformTexture("u_Material.metallicMap", 3);

		m_AOMap->Bind(4);
		m_Shader->SetUniformTexture("u_Material.aoMap", 4);
	}

	void Material::Validate() const
	{
		if (!m_Shader)
		{
			spdlog::error("Material is missing shader!");
			ASSERT(false);
			return;
		}
		if (!m_DiffuseMap)
		{
			spdlog::error("Diffuse Map not found in the material!");
		}
		if (!m_NormalMap)
		{
			spdlog::error("Normal map not found in the material!");
		}
		if (!m_RoughnessMap)
		{
			spdlog::error("Roughness map not found in the material!");
		}
		if (!m_MetallicMap)
		{
			spdlog::error("Metallic map not found in the material!");
		}
		if (!m_AOMap)
		{
			spdlog::error("AO map not found in the material!");
		}
	}
}