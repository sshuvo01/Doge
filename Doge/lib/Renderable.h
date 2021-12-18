#ifndef _DOGE_RENDERABLE_H_
#define _DOGE_RENDERABLE_H_
#include "Core.h"
#include <vector>
#include <glm/mat4x4.hpp>
#include "Material.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

namespace doge
{
	enum class RenderableType
	{
		_OPAQUE_ = 0,
		_TRANSPARENT_ = 1
	};
	// interface for anything that can be rendered
	class Renderable
	{
	public:
		NOCOPYNOASSIGN(Renderable);
		Renderable();
		Renderable(const RenderableType& type);
		virtual ~Renderable();
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void CleanUp() = 0;
		//------

		std::vector<glm::mat4>              m_ModelMats; // for multiple instances
		void BindData() const;
		std::shared_ptr<Material>			m_Material;
	protected:
		RenderableType                      m_Type;
		std::shared_ptr<VertexArray>        m_VAO;
		std::shared_ptr<VertexBuffer>       m_VB;
		std::shared_ptr<VertexBufferLayout> m_VBL;
		std::shared_ptr<IndexBuffer>        m_IB;
		//-----//
	};
}

#endif // !_DOGE_RENDERABLE_H_

