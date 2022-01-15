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

	class Framebuffer final
	{
	public:
		NOCOPYNOASSIGN(Framebuffer);
		Framebuffer() = delete;
		Framebuffer (const FramebufferSpec& spec);
		~Framebuffer();
		
		void BindFramebuffer() const;
		void UnbindFramebuffer() const;
		void BindTexture(uint slot = 0, uint colorbufferIndex = 0) const;
		static void BindDefault();
	private:
		FramebufferSpec       m_Spec;
		uint                  m_FramebufferID;
		uint                  m_RenderbufferID;
		uint*                 m_ColorbuffersID = nullptr;
	};
	//
	class DepthMap final
	{
	public:
		NOCOPYNOASSIGN(DepthMap);
		DepthMap() = delete;
		DepthMap(uint width = 1024, uint height = 1024);
		~DepthMap();

		void BindFramebuffer() const;
		void BindTexture(uint slot = 0) const;
		void UnbindFramebuffer() const;
		/*getters*/
		inline uint GetWidth() const { return m_Width; }
		inline uint GetHeight() const { return m_Height; }
	private:
		uint        m_FramebufferID, m_DepthMapID;
		uint        m_Width, m_Height;
	};
}

#endif // !_DOGE_FRAMEBUFFER_H_

