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
		FramebufferSpec fSpec;
		fSpec.isHDR = false;
		m_FBuffer1 = new Framebuffer{ fSpec };
		m_ScreenRectShader = new Shader{ "res/shaders/vert/ScreenRect.vert", "res/shaders/frag/ScreenRect.frag" };
	}
	
	Renderer::~Renderer()
	{
		DELETE(m_ScreenRectVAO);
		DELETE(m_ScreenRectVB);
		DELETE(m_ScreenRectVBL);
		DELETE(m_FBuffer1);
		DELETE(m_ScreenRectShader);
	}

	void Renderer::RenderFrame() const
	{
		SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		RenderDepthMaps();
		m_FBuffer1->BindFramebuffer();
		RenderRenderables();

		/*
		DirectionalLight* dlight = dynamic_cast<DirectionalLight*>( m_Scene->lightsList[1] );
		ASSERT(dlight);
		
		dlight->BindDepthMap();
		EnableDepthTest(true);
		ClearBuffer(false, true);

		dlight->BindShader();
		dlight->SetShaderUniforms();

		GLCALL(glViewport(0, 0, dlight->GetMapWidth(), dlight->GetMapHeight()));
		
		for (size_t r = 0; r < m_Scene->renderablesList.size(); r++)
		{
			const Renderable* rable = m_Scene->renderablesList[r];
			rable->BindData();
			GLCALL(glDrawElementsInstanced(GL_TRIANGLES, rable->GetIndexCount(), GL_UNSIGNED_INT, NULL, rable->GetModelMatsSize()));
		}
		*/
		
		Framebuffer::BindDefault();

		m_ScreenRectVAO->Bind();
		m_ScreenRectShader->Bind();
		//dlight->BindDepthTexture(0);
		m_FBuffer1->BindTexture(0);
		m_ScreenRectShader->SetUniformTexture("screenRectTexture", 0);

		GLCALL(glViewport(0, 0, m_ScreenWidth, m_ScreenHeight));
		EnableDepthTest(false);
		GLCALL(glDrawArrays(GL_TRIANGLES, 0, 6));
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
		spdlog::debug("Loaded screen rect vertices");// no index buffer
	}

	void Renderer::RenderRenderables() const
	{
		EnableDepthTest(true);
		ClearBuffer(true, true);
		GLCALL(glViewport(0, 0, m_ScreenWidth, m_ScreenHeight));
		for (size_t i = 0; i < m_Scene->renderablesList.size(); i++)
		{
			const Renderable* rable = m_Scene->renderablesList[i];
			rable->BindData();
			rable->GetMaterial()->SetMaterialUniforms();
			auto rshader = rable->GetMaterial()->GetShader();

			rshader->SetUniformMatrix4f("u_View", m_ViewMat);
			rshader->SetUniformMatrix4f("u_Projection", m_ProjectionMat);
						
			SetLightsUniforms(rshader);

			GLCALL(glDrawElementsInstanced(GL_TRIANGLES, rable->GetIndexCount(), GL_UNSIGNED_INT, NULL, rable->GetModelMatsSize()));
		}
	}

	void Renderer::ClearBuffer(bool color, bool depth, bool stencil, bool accum) const
	{
		GLbitfield mask = 0;

		if (color)
		{
			mask = mask | GL_COLOR_BUFFER_BIT;
		}
		if (depth)
		{
			mask = mask | GL_DEPTH_BUFFER_BIT;
		}
		if (stencil)
		{
			mask = mask | GL_STENCIL_BUFFER_BIT;
		}
		if (accum)
		{
			mask = mask | GL_ACCUM_BUFFER_BIT;
		}

		if (mask != 0) GLCALL(glClear(mask));
	}

	void Renderer::SetClearColor(const glm::vec4 & color) const
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::EnableDepthTest(bool state) const
	{
		if (state)
		{
			GLCALL(glEnable(GL_DEPTH_TEST));
		}
		else
		{
			GLCALL(glDisable(GL_DEPTH_TEST));
		}
	}

	void Renderer::EnableStencilTest(bool state) const
	{
		if (state)
		{
			GLCALL(glEnable(GL_STENCIL_TEST));
		}
		else
		{
			GLCALL(glDisable(GL_STENCIL_TEST));
		}
	}

	void Renderer::EnableDepthWriting(bool state) const
	{
		if (state)
		{
			GLCALL(glDepthMask(GL_TRUE));
		}
		else
		{
			GLCALL(glDepthMask(GL_FALSE));
		}
	}

	void Renderer::RenderDepthMaps() const
	{
		EnableDepthTest(true);

		for (size_t i = 0; i < m_Scene->lightsList.size(); i++)
		{
			// only for directional lights
			if (m_Scene->lightsList[i]->GetType() != LightType::DIRECTIONAL)
			{
				continue;
			}

			DirectionalLight* alight = dynamic_cast<DirectionalLight*>(m_Scene->lightsList[i]);
			ASSERT(alight);
			
			GLCALL(glViewport(0, 0, alight->GetMapWidth(), alight->GetMapHeight()));

			alight->BindDepthMap(); // bound depth map
			ClearBuffer(false, true);
			alight->SetShaderUniforms();
			//alight->BindShader();
			
			// render to the bound depth map
			for (size_t r = 0; r < m_Scene->renderablesList.size(); r++)
			{
				const Renderable* rable = m_Scene->renderablesList[r];
				rable->BindData();
				GLCALL(glDrawElementsInstanced(GL_TRIANGLES, rable->GetIndexCount(), GL_UNSIGNED_INT, NULL, rable->GetModelMatsSize()));
			}

			
		}
	}

	void Renderer::SetLightsUniforms(const std::shared_ptr<Shader>& shader) const
	{
		uint dirIndex = 0;
		uint pointIndex = 0;
		for (size_t i = 0; i < m_Scene->lightsList.size(); i++)
		{
			//shader->SetUniform1i("u_DirLightsCount", 1);
			Light* alight = m_Scene->lightsList[i];
			DirectionalLight* dlight = nullptr;
			
			switch (alight->GetType())
			{
			case LightType::DIRECTIONAL:
				dlight = dynamic_cast<DirectionalLight*>(alight);
				ASSERT(dlight);
				shader->SetUniform3f(Shader::GetUniformName("u_DirLights", dirIndex, "direction"), dlight->GetDirection());
				shader->SetUniform3f(Shader::GetUniformName("u_DirLights", dirIndex, "color"), dlight->GetColor());
				shader->SetUniform3f(Shader::GetUniformName("u_DirLights", dirIndex, "position"), dlight->GetPosition());

				dlight->BindDepthTexture(1 + static_cast<int>(dirIndex) ); // remember to change this later!
				shader->SetUniformTexture(Shader::GetUniformName("u_DirLights", dirIndex, "depthMap"), 1 + static_cast<int>(dirIndex) );
				shader->SetUniformMatrix4f(Shader::GetUniformName("u_DirLights", dirIndex, "lightSpaceMat"), dlight->GetLightSpaceMat());				
				
				dirIndex++;
				break;
			case LightType::POINT:
				pointIndex++;
				break;
			default:
				break;
			}
		}

		shader->SetUniform1i("u_DirLightsCount", static_cast<int>(dirIndex));
	}

}