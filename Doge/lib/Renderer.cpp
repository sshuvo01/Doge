#include "Renderer.h"

namespace doge
{
	Renderer::Renderer()
	{
	}
	
	Renderer::~Renderer()
	{
	}

	void Renderer::RenderThemAll(const glm::mat4& view, const glm::mat4& proj)
	{
		for (size_t i = 0; i < m_Renderables.size(); i++)
		{
			m_Renderables[i]->BindData();
			//m_Renderables[i]->m_Material->m_Shader->SetUniformMatrix4f("")
			m_Renderables[i]->m_Material->SetMaterialUniforms();
			m_Renderables[i]->m_Material->m_Shader->SetUniformMatrix4f("u_View", view);
			m_Renderables[i]->m_Material->m_Shader->SetUniformMatrix4f("u_Projection", proj);
			glm::mat4 vp = proj * view;

			for (size_t j = 0; j < m_Renderables[i]->m_ModelMats.size(); j++)
			{
				m_Renderables[i]->m_Material->m_Shader->SetUniformMatrix4f("u_Model", m_Renderables[i]->m_ModelMats[j]);
				glm::mat4 mvp = vp * m_Renderables[i]->m_ModelMats[j];
				m_Renderables[i]->m_Material->m_Shader->SetUniformMatrix4f("u_MVP", mvp);

				GLCALL(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL));
			}
		}

	}
}