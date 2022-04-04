#include "Texture.h"
#include "stb/stb_image.h"

namespace doge
{

	Texture::Texture(const std::string & path, bool flipUV, bool gamma,  GLenum repeatMode)
		: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr),
		  m_Width(0), m_Height(0), m_BPP(0)
	{
		//if(flipUV) stbi_set_flip_vertically_on_load(1);
		stbi_set_flip_vertically_on_load(flipUV);
		m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);

		if (m_LocalBuffer)
		{

		}
		else
		{
			spdlog::error("STBI_LOAD FAILED. Failed to load {}", path);
			ASSERT(false);
		}

		GLenum format;
		GLenum internalFormat;

		if (m_BPP == 1)
		{
			format = GL_RED;
			internalFormat = GL_RED;
		}
		else if (m_BPP == 3)
		{
			format = GL_RGB;
			internalFormat = gamma ? GL_SRGB : GL_RGB;
		}
		else if (m_BPP == 4)
		{
			format = GL_RGBA;
			internalFormat = gamma ? GL_SRGB_ALPHA : GL_RGBA;
		}
	
		GLCALL(glGenTextures(1, &m_RendererID));
		GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer));

		GLCALL( glGenerateMipmap(GL_TEXTURE_2D) );

		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeatMode));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeatMode));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		
		spdlog::debug("Loaded {}. Width {}, Height {}, Channels {}", m_FilePath, m_Width, m_Height, m_BPP);
	}

	Texture::~Texture()
	{
		GLCALL(glDeleteTextures(1, &m_RendererID));
		DELETE(m_LocalBuffer);
	}

	void Texture::Bind(unsigned int slot) const
	{
		GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
		GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	}

	void Texture::Unbind() const
	{
		//GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
	}

}
