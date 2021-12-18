#ifndef _DOGE_RENDERER_H_
#define _DOGE_RENDERER_H_
#include "Core.h"	
#include "Renderable.h"
#include "Camera.h"

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
	private:
		// special shaders are required
		
	};
}


#endif // !_DOGE_RENDERER_H_
