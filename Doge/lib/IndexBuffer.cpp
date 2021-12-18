#include "IndexBuffer.h"
#include "Core.h"

namespace doge
{
	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) 
		: m_Count(count)
	{
		ASSERT(sizeof(GLuint) == sizeof(unsigned int));
	
		GLCALL( glGenBuffers(1, &m_RendererID) );
		GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID) );
		GLCALL( glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW) );
	}

	IndexBuffer::IndexBuffer(unsigned int count) 
		: m_Count(count)
	{
		ASSERT(sizeof(GLuint) == sizeof(unsigned int));

		unsigned int* indices = new unsigned int[m_Count];

		for (int i = 0; i < m_Count; i++)
		{
			indices[i] = i;
		} // end of for

		GLCALL(	glGenBuffers(1, &m_RendererID) );
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
		GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), indices, GL_STATIC_DRAW));

		delete[] indices;
	}

	IndexBuffer::~IndexBuffer()
	{
		GLCALL(glDeleteBuffers(1, &m_RendererID));
	}

	void IndexBuffer::Bind() const
	{
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

	void IndexBuffer::Unbind() const
	{
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}


}
