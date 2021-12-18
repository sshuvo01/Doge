#include "Core.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

namespace doge
{
	VertexArray::VertexArray()
	{
		GLCALL( glGenVertexArrays(1, &m_RendererID) );
		GLCALL( glBindVertexArray(m_RendererID) );
		spdlog::debug("Constructed VAO. VAO ID: {}", m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		GLCALL( glDeleteVertexArrays(1, &m_RendererID) ); 
	}

	void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbl)
	{
		Bind();

		vb.Bind();
		auto& elements = vbl.GetElements();
	
		for (int i = 0; i < elements.size(); i++)
		{
			auto& elm = elements[i];
		
			GLCALL( glEnableVertexAttribArray(i) );
			GLCALL( glVertexAttribPointer(i, elm.count, elm.type, elm.normalized, 
				vbl.GetStride(), (const void*) elm.offset) );
		}

		spdlog::debug("Added buffer. VAO ID: {}, No. of Attributes {}", m_RendererID, elements.size());
	}

	void VertexArray::AddInstanceBuffer(const VertexBuffer& vb, DataType type, unsigned int index,
		unsigned int divisor)
	{
		/*separate buffer for instance array*/
		/*all floats*/
		Bind();
		vb.Bind();

		int count = (int)type;
	
		if (count <= 4)
		{
			GLCALL(glEnableVertexAttribArray(index));
			GLCALL(glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, 
				count * sizeof(float), (void*)0));
			GLCALL(glVertexAttribDivisor(index, divisor));
		}
		else
		{
			/*for matrix*/
			int vecSize;
			int vecElementCount = (int)sqrt(count);
			if (count == 16) vecSize = sizeof(glm::vec4);
			else if (count == 9) vecSize = sizeof(glm::vec3);

			for (int i = 0; i < vecElementCount; i++)
			{
				GLCALL(glEnableVertexAttribArray(index+i));
				GLCALL(glVertexAttribPointer(index+i, vecElementCount, GL_FLOAT, GL_FALSE, 
					vecElementCount * vecSize, (void*)(i*vecSize)));
				GLCALL(glVertexAttribDivisor(index+i, divisor));
			}
		} // end of else
	}

	void VertexArray::Bind() const
	{
		GLCALL(glBindVertexArray(m_RendererID));
		spdlog::debug("Bound VAO. VAO ID: {}", m_RendererID);
	}

	void VertexArray::Unbind() const
	{
		GLCALL(glBindVertexArray(0));
	}


}
