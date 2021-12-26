#include "Renderer.h"
#include "VertexBufferLayout.h"

namespace doge
{
	Renderer::Renderer()
		: m_ScreenWidth(640 * 2), m_ScreenHeight(480 * 2)
	{
		//m_Scene->lightsList.size();
		
		//m_ProjectionMat = 
		LoadScreenRectData();
	}
	
	Renderer::~Renderer()
	{
		DELETE(m_ScreenRectVAO);
		DELETE(m_ScreenRectVB);
		DELETE(m_ScreenRectVBL);
	}

	void Renderer::RenderThemAll(const glm::mat4& view, const glm::mat4& proj)
	{
		for (size_t i = 0; i < m_Scene->renderablesList.size(); i++)
		{
			const Renderable* rable = m_Scene->renderablesList[i];
			rable->BindData();

		}

		for (size_t i = 0; i < m_Renderables.size(); i++)
		{
			m_Renderables[i]->BindData();
			//m_Renderables[i]->m_Material->m_Shader->SetUniformMatrix4f("")
			m_Renderables[i]->GetMaterial()->SetMaterialUniforms();
			//m_Renderables[i]->m_Material->SetMaterialUniforms();
			m_Renderables[i]->GetMaterial()->GetShader()->SetUniformMatrix4f("u_View", view);
			m_Renderables[i]->GetMaterial()->GetShader()->SetUniformMatrix4f("u_Projection", proj);
			//m_Renderables[i]->m_Material->m_Shader->SetUniformMatrix4f("u_View", view);
			//m_Renderables[i]->m_Material->m_Shader->SetUniformMatrix4f("u_Projection", proj);
			glm::mat4 vp = proj * view;
			/*

			for (size_t j = 0; j < m_Renderables[i]->m_ModelMats.size(); j++)
			{
				m_Renderables[i]->m_Material->m_Shader->SetUniformMatrix4f("u_Model", m_Renderables[i]->m_ModelMats[j]);
				glm::mat4 mvp = vp * m_Renderables[i]->m_ModelMats[j];
				m_Renderables[i]->m_Material->m_Shader->SetUniformMatrix4f("u_MVP", mvp);

				GLCALL(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL));
			}
			*/
			glDrawElementsInstanced(GL_TRIANGLES, m_Renderables[i]->GetIndexCount(), 
				GL_UNSIGNED_INT, NULL, m_Renderables[i]->GetModelMatsSize());

		}

	}

	void Renderer::RenderThemAll() const
	{
		for (size_t i = 0; i < m_Scene->renderablesList.size(); i++)
		{
			const Renderable* rable = m_Scene->renderablesList[i];
			rable->BindData();
			rable->GetMaterial()->SetMaterialUniforms();
			rable->GetMaterial()->GetShader()->SetUniformMatrix4f("u_View", m_ViewMat);
			rable->GetMaterial()->GetShader()->SetUniformMatrix4f("u_Projection", m_ProjectionMat);
			
			glDrawElementsInstanced(GL_TRIANGLES, rable->GetIndexCount(),
				GL_UNSIGNED_INT, NULL, rable->GetModelMatsSize());
		}
	}

	void Renderer::LoadScreenRectData()
	{
		float screenRect[] =
		{
			// positions   // texCoords
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f, 1.0f
		};
		
		m_ScreenRectVB = new VertexBuffer(screenRect, sizeof(float) * (2 + 2) * 6);
		m_ScreenRectVBL = new VertexBufferLayout;
		m_ScreenRectVBL->Push(2);
		m_ScreenRectVBL->Push(2);
		m_ScreenRectVAO = new VertexArray;
		m_ScreenRectVAO->AddBuffer(*m_ScreenRectVB, *m_ScreenRectVBL);
		spdlog::debug("Loaded screen rect.");// no index buffer
	}
}