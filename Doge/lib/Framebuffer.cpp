#include "Framebuffer.h"
#include <iostream>
#include <vector>

namespace doge
{
	void Framebuffer::BindDefault()
	{
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	Framebuffer::Framebuffer(const FramebufferSpec& spec)
		: m_Spec(spec)
	{
		spdlog::debug("Constructing framebuffer");

		GLCALL(glGenFramebuffers(1, &m_FramebufferID));
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID));

		//color attachment texture
		m_ColorbuffersID = new uint[m_Spec.colorBufferCount];
		GLCALL(glGenTextures(m_Spec.colorBufferCount, m_ColorbuffersID));
		GLenum internalFormat = m_Spec.isHDR ? GL_RGBA16F : GL_RGBA;

		for (uint i = 0; i < m_Spec.colorBufferCount; i++)
		{
			GLCALL(glBindTexture(GL_TEXTURE_2D, m_ColorbuffersID[i]));
			GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Spec.width, m_Spec.height, 0, GL_RGBA, GL_FLOAT, NULL));
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)m_Spec.texFilteringMode));
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)m_Spec.texFilteringMode));
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)m_Spec.texRepeatMode));
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)m_Spec.texRepeatMode));
			GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_ColorbuffersID[i], 0));
		} // end of for

		GLCALL(glGenRenderbuffers(1, &m_RenderbufferID));
		GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, m_RenderbufferID));
		GLCALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Spec.width, m_Spec.height));
		GLCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderbufferID));

		std::vector<uint> attachments;
		for (uint i = 0; i < m_Spec.colorBufferCount; i++)
		{
			attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
		}
		GLCALL(glDrawBuffers(m_Spec.colorBufferCount, (const GLenum*)&attachments[0]));

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			spdlog::error("Framebuffer not complete!");
			ASSERT(false);
		}
		else if ( glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
		{
			spdlog::debug("Framebuffer created");
		}
		UnbindFramebuffer();
	}

	Framebuffer::~Framebuffer()
	{
		GLCALL(glDeleteFramebuffers(1, &m_FramebufferID));
		GLCALL(glDeleteRenderbuffers(1, &m_RenderbufferID));
		GLCALL(glDeleteTextures(m_Spec.colorBufferCount, m_ColorbuffersID));

		DELETEARRAY(m_ColorbuffersID);
	}

	void Framebuffer::BindFramebuffer() const
	{
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID));
	}

	void Framebuffer::UnbindFramebuffer() const
	{
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void Framebuffer::BindTexture(uint slot, uint colorbufferIndex) const
	{
		if (colorbufferIndex < m_Spec.colorBufferCount)
		{
			GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
			GLCALL(glBindTexture(GL_TEXTURE_2D, m_ColorbuffersID[colorbufferIndex]));
		}
		else
		{
			spdlog::error("Color Buffer Index {} is out of bound", colorbufferIndex);
			ASSERT(false);
		}
	}
	//----------------//
	DepthMap::DepthMap(uint width, uint height)
		: m_Width(width), m_Height(height)
	{
		spdlog::debug("Constructing depth map, width {}, height {}", m_Width, m_Height);
		GLCALL(glGenFramebuffers(1, &m_FramebufferID));
		GLCALL(glGenTextures(1, &m_DepthMapID));
		GLCALL(glBindTexture(GL_TEXTURE_2D, m_DepthMapID));
		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
		float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLCALL(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));

		/*bind the frame buffer*/
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID));
		GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthMapID, 0));
		GLCALL(glDrawBuffer(GL_NONE));
		GLCALL(glReadBuffer(GL_NONE));

		if (GL_FRAMEBUFFER_COMPLETE != glCheckFramebufferStatus(GL_FRAMEBUFFER))
		{
			spdlog::debug("Failed to create depth map");
			ASSERT(false);
		}
		else
		{
			spdlog::debug("Depth map constructed. Width: {}, Height: {}", m_Width, m_Height);
		}

		UnbindFramebuffer();
	}

	DepthMap::~DepthMap()
	{
	}

	void DepthMap::BindTexture(uint slot) const
	{
		GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
		GLCALL(glBindTexture(GL_TEXTURE_2D, m_DepthMapID));
	}

	void DepthMap::BindFramebuffer() const
	{
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID));
	}

	void DepthMap::UnbindFramebuffer() const
	{
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}


} // end of doge