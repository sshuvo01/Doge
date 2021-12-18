#ifndef _DOGE_VERTEXBUFFER_H_
#define _DOGE_VERTEXBUFFER_H_
#include "Core.h"

namespace doge
{
	class VertexBuffer
	{
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();
		VertexBuffer() = delete;

		/*
		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer(const VertexBuffer&&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&&) = delete;
		*/
		NOCOPYNOASSIGN(VertexBuffer);

		void Bind() const;
		void Unbind() const;
	private:
		unsigned int m_RendererID;
	};
}

#endif // !_DOGE_VERTEXBUFFER_H_
