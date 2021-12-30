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
		m_FBuffer1 = new Framebuffer{fSpec};
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
		m_FBuffer1->BindFramebuffer();

		SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		ClearBuffer(true, true);
		EnableDepthTest(true);

		RenderRenderables();

		m_FBuffer1->UnbindFramebuffer();
		//
		m_ScreenRectVAO->Bind();
		m_ScreenRectShader->Bind();
		m_FBuffer1->BindTexture();
		m_ScreenRectShader->SetUniformTexture("screenRectTexture", 0);
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
		for (size_t i = 0; i < m_Scene->renderablesList.size(); i++)
		{
			const Renderable* rable = m_Scene->renderablesList[i];
			rable->BindData();
			rable->GetMaterial()->SetMaterialUniforms();
			rable->GetMaterial()->GetShader()->SetUniformMatrix4f("u_View", m_ViewMat);
			rable->GetMaterial()->GetShader()->SetUniformMatrix4f("u_Projection", m_ProjectionMat);

			GLCALL(glDrawElementsInstanced(GL_TRIANGLES, rable->GetIndexCount(),
				GL_UNSIGNED_INT, NULL, rable->GetModelMatsSize()));
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



}