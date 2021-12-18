#include "Renderable.h"

namespace doge
{
	Renderable::Renderable()
		:m_Type{ RenderableType::_OPAQUE_ }
	{
		spdlog::debug("Constructed opaque renderable");
	}

	Renderable::Renderable(const RenderableType & type)
		:m_Type{ type }
	{
		std::string name = m_Type == RenderableType::_OPAQUE_ ? "opaque" : "transparent";
		spdlog::debug("Constructed {} renderable", name);
	}

	Renderable::~Renderable()
	{
		spdlog::debug("Destroying renderable");
	}

	void Renderable::BindData() const
	{
		m_VAO->Bind();
		m_IB->Bind();
		m_Material->m_Shader->Bind();
	}
}


