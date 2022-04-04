#ifndef _DOGE_CUBEMAP_H_
#define _DOGE_CUBEMAP_H_
#include "Core.h"
#include "Texture.h"

namespace doge
{
	class Cubemap final
	{
	public:
		NOCOPYNOASSIGN(Cubemap);
		Cubemap() = delete;
		Cubemap(const std::string& dir, const std::string* face, bool flipTexture = false);
		~Cubemap();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;
	private:
		unsigned int        m_RendererID;
		std::string         m_Directory, m_FacesName[6];
		unsigned char*      m_LocalBuffer[6];
		int                 m_Width[6], m_Height[6], m_BPP[6];
	};
}

#endif // !_DOGE_CUBEMAP_H_
