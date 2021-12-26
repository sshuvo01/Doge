#include "Renderable.h"
#include "VertexBufferLayout.h"

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
		ASSERT(m_VAO);
		m_VAO->Bind();
		m_IB->Bind();
		m_Material->GetShader()->Bind();
	}

	void Renderable::AddData(const RenderableData& rData, const std::vector<glm::mat4>& modelMats)
	{
		spdlog::debug("Adding renderable data\n");
		if (rData.buffer)
		{
			m_VB = std::make_shared<VertexBuffer>(rData.buffer, rData.bufferSize);
			spdlog::debug("Buffer size in bytes {}", rData.bufferSize);
		}
		else
		{
			spdlog::error("Buffer is not set!");
		}

		if (rData.index)
		{
			m_IB = std::make_shared<IndexBuffer>(rData.index, rData.indexCount);
			spdlog::debug("Index buffer created. Count: {}", rData.indexCount);
		}
		else
		{
			if (rData.indexCount == 0)
			{
				spdlog::error("No information on IB. Index buffer could not be set!");
				ASSERT(false);
			}
			else
			{
				m_IB = std::make_shared<IndexBuffer>(rData.indexCount);
				spdlog::debug("Index buffer created. Count: {}", rData.indexCount);
			}
		}

		if (!rData.layout)
		{
			spdlog::error("Layout not set!");
			ASSERT(false);
		}
		else
		{
			m_VBL = std::make_shared<VertexBufferLayout>();
			for (uint i = 0; i < rData.layoutCount; i++)
			{
				m_VBL->Push(rData.layout[i]);
			}
			spdlog::debug("Layout set. Count: {}", rData.layoutCount);
		}

		m_VAO = std::make_shared<VertexArray>();
		m_VAO->AddBuffer(*m_VB, *m_VBL);

		// instance buffer
		ASSERT(modelMats.size() > 0);
		m_ModelMats = modelMats;
		m_InstanceBuffer = std::make_shared<VertexBuffer>(m_ModelMats.data(), sizeof(glm::mat4) * m_ModelMats.size());
		m_VAO->AddInstanceBuffer(*m_InstanceBuffer, DataType::MAT4, 3, 1);
	}

	


} // namespace doge


