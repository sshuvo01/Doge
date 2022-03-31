#include "ModelLoader.h"
#include <iostream>

namespace doge
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint>& indices, const std::vector<MaterialMap>& maps)
		:m_Vertices{vertices}, m_Indices{indices}, m_MaterialMaps{maps}
	{

		spdlog::debug("Created mesh with {} vertices, {} indices, {} maps", m_Vertices.size(), m_Indices.size(), m_MaterialMaps.size());
	}

	Mesh::~Mesh()
	{
	}

	// model class
	Model::Model(const std::string & filename)
		: m_Filename(filename)
	{
		spdlog::debug("Loading model {}", m_Filename);

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(m_Filename, aiProcess_Triangulate | aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{	
			spdlog::error("Could not load model {}, reason: {}", m_Filename, importer.GetErrorString());
			return;
		}

		m_Directoryname = m_Filename.substr(0, m_Filename.find_last_of('/'));
		ProcessNode(scene->mRootNode, scene);
		spdlog::debug("Loaded {} with {} meshes", m_Filename, m_MeshList.size());
	}

	Model::~Model()
	{
	}

	void Model::ProcessNode(const aiNode * node, const aiScene * scene)
	{
		for (uint i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_MeshList.push_back(ProcessMesh(mesh, scene));
		}

		for (uint i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::ProcessMesh(const aiMesh * mesh, const aiScene * scene)
	{
		std::vector<Vertex> vertices;
		std::vector<uint> indices;
		std::vector<MaterialMap> materialMaps;


		for (uint i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector;
			// positions
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;
			// normals
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
			// texture coordinates
			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;

				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.texCoord = vec;
			}
			else
			{
				vertex.texCoord = glm::vec2(0.0f, 0.0f);
			}
			
			// tangent
			
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.tangent = vector;

			//bitangent
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.bitangent = vector;
			
			vertices.push_back(vertex);
		} // end of for

		// indices
		for (uint k = 0; k < mesh->mNumFaces; k++)
		{
			aiFace face = mesh->mFaces[k];
			for (uint j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}
		// material maps
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		
		
		//auto counttt = material->GetTextureCount(aiTextureType_AMBIENT);
		// aiTextureType_SHININESS = obj map_Ns = metallic map 
		// aiTextureType_SPECULAR = obj map_Ks = roughness map 
		// aiTextureType_AMBIENT = obj map_Ka = ambient occlusion map 
		// aiTextureType_HEIGHT = obj map_Bump = normal map
		// aiTextureType_DIFFUSE = obj map_Kd = albedo map
		//std::cout << counttt << std::endl;
		//std::cin.get();

		auto diffuseMaps = LoadMaterialMaps(material, MaterialMapType::DIFFUSE);
		auto normalMaps = LoadMaterialMaps(material, MaterialMapType::NORMAL);
		auto roughnessMaps = LoadMaterialMaps(material, MaterialMapType::ROUGHNESS);
		auto metallicMaps = LoadMaterialMaps(material, MaterialMapType::METALLIC);
		auto aoMaps = LoadMaterialMaps(material, MaterialMapType::AMBIENTOCCLUSION);

		materialMaps.insert(materialMaps.end(), diffuseMaps.begin(), diffuseMaps.end());
		materialMaps.insert(materialMaps.end(), normalMaps.begin(), normalMaps.end());
		materialMaps.insert(materialMaps.end(), roughnessMaps.begin(), roughnessMaps.end());
		materialMaps.insert(materialMaps.end(), metallicMaps.begin(), metallicMaps.end());
		materialMaps.insert(materialMaps.end(), aoMaps.begin(), aoMaps.end());

		return { vertices, indices, materialMaps };
	}

	std::vector<MaterialMap> Model::LoadMaterialMaps(const aiMaterial * mat, const MaterialMapType & type)
	{
		std::vector<MaterialMap> maps;
		std::string mapTypeName;
		aiTextureType aiType = GetTextureType(type, mapTypeName);
		
		spdlog::debug("Loading {} {} maps", mat->GetTextureCount(aiType), mapTypeName);
		// shared pointer
		// type
		for (uint i = 0; i < mat->GetTextureCount(aiType); i++)
		{
			aiString mapname;
			mat->GetTexture(aiType, i, &mapname);
			
			MaterialMap theMap;
			std::string textureName = m_Directoryname + "/" + std::string{ mapname.C_Str() };
			theMap.mapTexture = std::make_shared<Texture>(textureName, false, false);
			
			/*
			if (type == MaterialMapType::DIFFUSE)
			{
				theMap.mapTexture = std::make_shared<Texture>(lolo, false, false);
			}
			else if(type == MaterialMapType::NORMAL)
			{
				theMap.mapTexture = std::make_shared<Texture>(lolo, false, false);
			}
			else if (type == MaterialMapType::ROUGHNESS)
			{
				theMap.mapTexture = std::make_shared<Texture>(lolo, false, false);
			}
			else if(type == MaterialMapType::METALLIC)
			{

			}
			else if (type == MaterialMapType::AMBIENTOCCLUSION)
			{

			}
			*/

			theMap.type = type;
			maps.push_back(theMap);
			spdlog::debug("Loaded {} as {} map", mapname.C_Str(), mapTypeName);
		}
		
		return maps;
	}

	const aiTextureType Model::GetTextureType(const MaterialMapType & type, std::string& typeName) const
	{
		// TODO:: add more maps later
		switch (type)
		{
		case MaterialMapType::DIFFUSE:
			typeName = "DIFFUSE";
			return aiTextureType::aiTextureType_DIFFUSE;
			break;
		case MaterialMapType::NORMAL:
			typeName = "NORMAL";
			return aiTextureType::aiTextureType_HEIGHT; // weird!
			break;
		case MaterialMapType::ROUGHNESS:
			typeName = "ROUGHNESS";
			return aiTextureType::aiTextureType_SPECULAR; // uwu
			break;
		case MaterialMapType::METALLIC:
			typeName = "METALLIC";
			return aiTextureType::aiTextureType_SHININESS;
			break;
		case MaterialMapType::AMBIENTOCCLUSION:
			typeName = "AMBIENTOCCLUSION";
			return aiTextureType::aiTextureType_AMBIENT;
			break;
		default:
			typeName = "UNKNOWN";
			return aiTextureType::aiTextureType_UNKNOWN;
			break;
		}
	}
}