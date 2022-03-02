#ifndef _DOGE_RENDERABLE_H_
#define _DOGE_RENDERABLE_H_
#include "Core.h"
#include <vector>
#include <memory>
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
	struct RenderableData
	{
		const float* buffer = nullptr;
		uint bufferSize = 0;
		const uint* index = nullptr;
		uint indexCount = 0;
		const uint* layout = nullptr;
		uint layoutCount = 0; // array size, not byte
	};
	// interface for anything that can be rendered
	class Renderable
	{
	public:
		NOCOPYNOASSIGN(Renderable);
		Renderable();
		Renderable(const RenderableType& type);
		virtual ~Renderable();
		virtual void Init() { }
		virtual void Update() { } 
		virtual void CleanUp() { }
		//------

		void BindData() const;
		inline const std::shared_ptr<Material>& GetMaterial() const { return m_Material; }
		//inline void SetMaterial(const std::shared_ptr<Material>& material) { m_Material = material; }
		inline uint GetModelMatsSize() const { return m_ModelMats.size(); }
		inline uint GetIndexCount() const { return m_IB->GetCount(); }
		void AddData(const RenderableData& rData, const std::vector<glm::mat4>& modelMats, const std::shared_ptr<Material>& mat);
	private:
		std::vector<glm::mat4>              m_ModelMats; // for multiple instances
		RenderableType                      m_Type;
		std::shared_ptr<VertexArray>        m_VAO;
		std::shared_ptr<VertexBuffer>       m_VB, m_InstanceBuffer;
		std::shared_ptr<VertexBufferLayout> m_VBL;
		std::shared_ptr<IndexBuffer>        m_IB;
		std::shared_ptr<Material>			m_Material;
		//-----//
	};
}

#endif // !_DOGE_RENDERABLE_H_

