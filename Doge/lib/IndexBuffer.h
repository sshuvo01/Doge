#ifndef _DOGE_INDEXBUFFER_H_
#define _DOGE_INDEXBUFFER_H_
#include "Core.h"

namespace doge
{
	class IndexBuffer
	{
	public:
		NOCOPYNOASSIGN(IndexBuffer);
		IndexBuffer(const unsigned int* data, unsigned int count);
		IndexBuffer(unsigned int count);
		IndexBuffer() = delete;
		~IndexBuffer();
		
		void Bind() const;
		void Unbind() const;
		inline unsigned int GetCount() const { return m_Count; }
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};

}

#endif // !_DOGE_INDEXBUFFER_H_