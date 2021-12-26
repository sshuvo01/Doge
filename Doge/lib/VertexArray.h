#ifndef _DOGE_VERTEXARRAY_H_
#define _DOGE_VERTEXARRAY_H_
#include "Core.h"
#include "VertexBuffer.h"

namespace doge
{
	enum class DataType
	{
		MAT3 = 9, MAT4 = 16, VEC2 = 2, VEC3 = 3, VEC4 = 4
	};

	class VertexBufferLayout;

	class VertexArray
	{
	public:
		NOCOPYNOASSIGN(VertexArray);
		VertexArray();
		~VertexArray();
		
		/*
		VertexArray(const VertexArray&) = delete;
		VertexArray(const VertexArray&&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&&) = delete;
		*/

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbl);
		void AddInstanceBuffer(const VertexBuffer& vb, DataType type, unsigned int index,
			unsigned int divisor);
		void Bind() const;
		void Unbind() const;
	private:
		unsigned int    m_RendererID;
	};

}

#endif // !_DOGE_VERTEXARRAY_H_