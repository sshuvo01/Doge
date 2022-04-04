#ifndef _DOGE_MODELLOADER_H_
#define _DOGE_MODELLOADER_H_
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "Core.h"
#include "Texture.h"

namespace doge
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoord;
		glm::vec3 tangent;
		glm::vec3 bitangent;
	};

	class Mesh final
	{
	public:
		Mesh() = delete;
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint> & indices, const std::vector<MaterialMap>& maps);
		~Mesh();
		
		std::vector<Vertex>        m_Vertices;
		std::vector<uint>          m_Indices;
		std::vector<MaterialMap>   m_MaterialMaps;
	private:
		
	};
	// model class, model = many meshes
	class Model final
	{
	public:
		NOCOPYNOASSIGN(Model);
		Model() = delete;
		Model(const std::string& filename, bool flipTexture = false);
		~Model();

		inline const std::vector<Mesh>& GetMeshList() const { return m_MeshList; }
		inline const std::string& GetFilename() const { return m_Filename; }

	private:
		std::string              m_Filename, m_Directoryname;
		std::vector<Mesh>        m_MeshList;
		bool                     m_FlipTexture;
		/*private functions*/
		void ProcessNode(const aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(const aiMesh* mesh, const aiScene* scene);
		std::vector<MaterialMap> LoadMaterialMaps(const aiMaterial * mat, const MaterialMapType& type);
		const aiTextureType GetTextureType(const MaterialMapType & type, std::string& typeName) const;
	};

}

#endif // !_DOGE_MODELLOADER_H_
