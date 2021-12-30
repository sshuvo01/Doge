#ifndef _DOGE_RENDERER_H_
#define _DOGE_RENDERER_H_
#include "Core.h"	
#include "Renderable.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Scene.h"

namespace doge
{
	class Renderer
	{
	public:
		NOCOPYNOASSIGN(Renderer);
		Renderer();
		~Renderer();

		std::vector<const Renderable*>      m_Renderables;
		void RenderFrame() const;
		inline void SetScene(const Scene* scene) { m_Scene = scene; }
		inline void SetViewMat(const glm::mat4& viewMat) { m_ViewMat = viewMat; }
		inline void SetProjectionMat(const glm::mat4& projectoinMat) { m_ProjectionMat = projectoinMat; }
		inline void SetCameraPosition(const glm::vec3& campos) { m_CameraPosition = campos; }
		//
		inline void SetWidth(uint screenWidth) { m_ScreenWidth = screenWidth; }
		inline void SetHeight(uint screenHeight) { m_ScreenHeight = screenHeight; }
		void ClearBuffer(bool color, bool depth, bool stencil = false, bool accum = false) const;
		void SetClearColor(const glm::vec4& color) const;
		void EnableDepthTest(bool state = true) const;
		void EnableStencilTest(bool state = true) const;
		void EnableDepthWriting(bool state = true) const;
	private:
		const Scene*          m_Scene = nullptr; // does not take ownership

		glm::mat4             m_ViewMat, m_ProjectionMat;
		glm::vec3             m_CameraPosition;

		uint                  m_ScreenWidth, m_ScreenHeight;
		VertexBuffer*         m_ScreenRectVB = nullptr;
		VertexBufferLayout*   m_ScreenRectVBL = nullptr;
		VertexArray*          m_ScreenRectVAO = nullptr;
		Framebuffer*          m_FBuffer1 = nullptr;
		Shader*               m_ScreenRectShader = nullptr;
		/*private functions*/
		void LoadScreenRectData();
		void RenderRenderables() const;

	};
}


#endif // !_DOGE_RENDERER_H_
