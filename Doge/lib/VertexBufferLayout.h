#ifndef _DOGE_VERTEXBUFFERLAYOUT_H_
#define _DOGE_VERTEXBUFFERLAYOUT_H_

#include "Core.h"
#include <vector>

namespace doge
{
	struct VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		unsigned int offset;
		GLboolean normalized;

		static unsigned int GetTypeSize(unsigned int type)
		{
			switch (type)
			{
			case GL_FLOAT:
				return sizeof(GLfloat);
			case GL_UNSIGNED_INT:
				return sizeof(GLuint);
			case GL_UNSIGNED_BYTE:
				return sizeof(GLubyte);
			default:
				ASSERT(false);
				break;
			}
			return 0;
		}
	};

	/*
	class VBLBase
	{

	};


	class VertexBufferLayout : public VBLBase
	{
	public:
		VertexBufferLayout() : m_Stride(0) { }
		template<typename T>
		void Push(unsigned int count)
		{
			static_assert(false);
		}

		template<>
		void Push<float>(unsigned int count)
		{
			m_Elements.push_back({ GL_FLOAT, count, m_Stride, GL_FALSE });
			m_Stride += (count * VertexBufferElement::GetTypeSize(GL_FLOAT));
		}

		template<>
		void Push<unsigned int>(unsigned int count)
		{
			m_Elements.push_back({ GL_UNSIGNED_INT, count, m_Stride, GL_FALSE });
			m_Stride += (count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT));
		}

		template<>
		void Push<unsigned char>(unsigned int count)
		{
			m_Elements.push_back({ GL_UNSIGNED_BYTE, count, m_Stride, GL_FALSE });
			m_Stride += (count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE));
		}

		inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
		inline const unsigned int& GetStride() const { return m_Stride; }
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	};
	*/

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout() : m_Stride(0) { }
		
		void Push(unsigned int count)
		{
			m_Elements.push_back({ GL_FLOAT, count, m_Stride, GL_FALSE });
			m_Stride += (count * VertexBufferElement::GetTypeSize(GL_FLOAT));
		}

		inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
		inline const unsigned int& GetStride() const { return m_Stride; }
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	};


}

#endif // !_DOGE_VERTEXBUFFERLAYOUT_H_
