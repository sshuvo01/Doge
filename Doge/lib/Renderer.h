#ifndef _DOGE_RENDERER_H_
#define _DOGE_RENDERER_H_
#include "Core.h"	
#include "Renderable.h"
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
		void RenderThemAll(const glm::mat4& view, const glm::mat4& proj);
		void RenderThemAll() const;
		inline void SetScene(const Scene* scene) { m_Scene = scene; }
		inline void SetViewMat(const glm::mat4& viewMat) { m_ViewMat = viewMat; }
		inline void SetProjectionMat(const glm::mat4& projectoinMat) { m_ProjectionMat = projectoinMat; }
		//
		inline void SetWidth(uint screenWidth) { m_ScreenWidth = screenWidth; }
		inline void SetHeight(uint screenHeight) { m_ScreenHeight = screenHeight; }
	private:
		const Scene*          m_Scene = nullptr; // does not take ownership
		glm::mat4             m_ViewMat, m_ProjectionMat;
		uint                  m_ScreenWidth, m_ScreenHeight;
		VertexBuffer*         m_ScreenRectVB = nullptr;
		VertexBufferLayout*   m_ScreenRectVBL = nullptr;
		VertexArray*          m_ScreenRectVAO = nullptr;
		// special shaders are required
		/*private functions*/
		void LoadScreenRectData();
	};
}


#endif // !_DOGE_RENDERER_H_
