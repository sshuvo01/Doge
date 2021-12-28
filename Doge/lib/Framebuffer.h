#ifndef _DOGE_FRAMEBUFFER_H_
#define _DOGE_FRAMEBUFFER_H_
#include "Core.h"

namespace doge
{
	struct FramebufferSpec
	{
		uint width = 640 * 2;
		uint height = 480 * 2;
		uint colorBufferCount = 1;
		GLenum texRepeatMode = GL_REPEAT;
		GLenum texFilteringMode = GL_LINEAR;
		bool isHDR = true;
	};

	class Framebuffer
	{
	public:
		NOCOPYNOASSIGN(Framebuffer);
		Framebuffer() = delete;
		Framebuffer (const FramebufferSpec& spec);
		~Framebuffer();
		
		void BindFramebuffer() const;
		void UnbindFramebuffer() const;
		void BindTexture(uint slot = 0, uint colorbufferIndex = 0) const;
	private:
		FramebufferSpec       m_Spec;
		uint                  m_FramebufferID;
		uint                  m_RenderbufferID;
		uint*                 m_ColorbuffersID = nullptr;
	};

}

#endif // !_DOGE_FRAMEBUFFER_H_

