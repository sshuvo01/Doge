#ifndef _DOGE_TEXTURE_H_
#define _DOGE_TEXTURE_H_
#include "Core.h"
#include "stb/stb_image.h"
#include <memory>

namespace doge
{
	class Texture;

	enum class MaterialMapType
	{
		DIFFUSE = 0x0,
		NORMAL,
		ROUGHNESS,
		METALLIC,
		AMBIENTOCCLUSION,
		UNKNOWN,
	};

	struct MaterialMap
	{
		std::shared_ptr<Texture> mapTexture = nullptr;
		MaterialMapType type = MaterialMapType::UNKNOWN;
	};

	class Texture final
	{
	public:
		NOCOPYNOASSIGN(Texture);
		Texture() = delete;
		Texture(const std::string& path, bool flipUV = false, bool gamma = false, GLenum repeatMode = GL_REPEAT);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		/* setters and getters */
		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
		inline std::string GetFilePath() const { return m_FilePath; }
		inline std::string GetFileName() const { return m_FileName; }
		inline void SetFileName(const std::string& fileName) { m_FileName = fileName; }

		inline unsigned int GetID() const { return m_RendererID; }
	private:
		unsigned int        m_RendererID;
		std::string         m_FilePath;
		std::string         m_FileName;
		unsigned char*      m_LocalBuffer;
		int                 m_Width, m_Height, m_BPP;
	};

}

#endif // !_DOGE_TEXTURE_H_
