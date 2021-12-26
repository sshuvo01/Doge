#include "Framebuffer.h"
#include <iostream>
#include <vector>

namespace doge
{

	Framebuffer::Framebuffer
	(
		unsigned int width, unsigned int height,
		FramebufferSettings settings,
		unsigned int colorbufferCount, bool isHDR
	)
		: m_ColorbuffesCount(colorbufferCount), m_Width(width), m_Height(height),
		m_Settings(settings), m_IsHDR(isHDR)
	{
		spdlog::debug("Constructing framebuffer");

		GLCALL(glGenFramebuffers(1, &m_FramebufferID));
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID));

		//color attachment texture
		m_ColorbuffersID = new unsigned int[m_ColorbuffesCount];
		GLCALL(glGenTextures(m_ColorbuffesCount, m_ColorbuffersID));
		GLenum internalFormat = m_IsHDR ? GL_RGBA16F : GL_RGBA;

		for (unsigned int i = 0; i < m_ColorbuffesCount; i++)
		{
			GLCALL(glBindTexture(GL_TEXTURE_2D, m_ColorbuffersID[i]));
			GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL));
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)m_Settings.texFilteringMode));
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)m_Settings.texFilteringMode));
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)m_Settings.texRepeatMode));
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)m_Settings.texRepeatMode));
			GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_ColorbuffersID[i], 0));
		} // end of for

		GLCALL(glGenRenderbuffers(1, &m_RenderbufferID));
		GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, m_RenderbufferID));
		GLCALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height));
		GLCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderbufferID));

		std::vector<unsigned int> attachments;
		for (unsigned int i = 0; i < m_ColorbuffesCount; i++)
		{
			attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
		}
		GLCALL(glDrawBuffers(m_ColorbuffesCount, (const GLenum*)&attachments[0]));

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
		GLCALL(glDeleteTextures(m_ColorbuffesCount, m_ColorbuffersID));

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

	void Framebuffer::BindTexture(unsigned int slot, unsigned int colorbufferIndex) const
	{
		GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
		GLCALL(glBindTexture(GL_TEXTURE_2D, m_ColorbuffersID[colorbufferIndex]));
	}


} // end of doge