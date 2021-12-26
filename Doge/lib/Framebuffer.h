#ifndef _DOGE_FRAMEBUFFER_H_
#define _DOGE_FRAMEBUFFER_H_
#include "Core.h"

namespace doge
{
	struct FramebufferSettings
	{
		GLenum texRepeatMode = GL_REPEAT;
		GLenum texFilteringMode = GL_LINEAR;
	};

	class Framebuffer
	{
	public:
		NOCOPYNOASSIGN(Framebuffer);
		Framebuffer
		(
			unsigned int width, unsigned int height,
			FramebufferSettings settings = FramebufferSettings(),
			unsigned int colorbufferCountbool = 1,
			bool isHDR = true
		);
		~Framebuffer();
		
		void BindFramebuffer() const;
		void UnbindFramebuffer() const;
		void BindTexture(unsigned int slot = 0, unsigned int colorbufferIndex = 0) const;
	private:
		unsigned int            m_Width;
		unsigned int            m_Height;
		bool                    m_IsHDR;
		FramebufferSettings     m_Settings;
		unsigned int            m_FramebufferID;
		unsigned int            m_RenderbufferID;
		unsigned int*           m_ColorbuffersID = nullptr;
		unsigned int            m_ColorbuffesCount;
	};

}

#endif // !_DOGE_FRAMEBUFFER_H_

