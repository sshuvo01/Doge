#include "Models.h"
#include "ModelLoader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace doge
{
	Models::Models(std::vector<Renderable*>& renderablesList)
	{
		spdlog::debug("Constructing models");
		// pushes all the meshes to the list as renderables
		m_TheModel = new Model{ "res/model/fox/low-poly-fox-by-pixelmannen.obj", true };
		size_t nOfMesh = m_TheModel->GetMeshList().size();
		m_Meshes = new Renderable[nOfMesh];
		
		uint layout[] = { 3, 3, 2, 3, 3 };
		std::vector<glm::mat4> modelMats; // master 
		glm::mat4 m{ 1.0f };
		m = glm::scale(m, { 0.05f, 0.05f, 0.05f });
		m = glm::translate(m, { 70.0f, -80.0f, 0.0f });
		//m = glm::rotate(m, glm::radians(45.0f), { 0.0f, 1.0f, 0.0f });
		
		modelMats.push_back(m);
		
		auto theShader = std::make_shared<Shader>("res/shaders/vert/Test.vert", "res/shaders/frag/Test.frag");

		for (size_t i = 0; i < nOfMesh; i++)
		{
			const Mesh& theMesh = m_TheModel->GetMeshList()[i];
			RenderableData rData;
			const void* a = static_cast<const void*>( &(theMesh.m_Vertices[0]) );
			rData.buffer = static_cast<const float*>(a);
			rData.bufferSize = sizeof(Vertex) * theMesh.m_Vertices.size();
			rData.layout = layout;
			rData.layoutCount = 5;

			rData.index = static_cast<const uint*>(&(theMesh.m_Indices[0]));
			//rData.index = nullptr;
			rData.indexCount = theMesh.m_Indices.size();

			auto material = std::make_shared<Material>();
			auto diffMap = ExtractTexture(i, MaterialMapType::DIFFUSE);
			
			if (!diffMap)
			{
				spdlog::error("Diffuse map not found!");
				ASSERT(false);
			}
			else
			{
				spdlog::debug("Name of the diffuse map: {}", diffMap->GetFilePath());
				material->SetDiffuseMap(diffMap);
			}

			auto normalMap = ExtractTexture(i, MaterialMapType::NORMAL);
			if (!normalMap)
			{
				spdlog::error("Normal map not found!");
				ASSERT(false);
			}
			else
			{
				spdlog::debug("Name of the normal map: {}", normalMap->GetFilePath());
				material->SetNormalMap(normalMap);
			}
			auto roughnessMap = ExtractTexture(i, MaterialMapType::ROUGHNESS);
			if (!roughnessMap)
			{
				spdlog::error("Roughness map not found!");
				ASSERT(false);
			}
			else
			{
				spdlog::debug("Name of the roughness map: {}", roughnessMap->GetFilePath());
				material->SetRoughnessMap(roughnessMap);
			}
			auto metallicMap = ExtractTexture(i, MaterialMapType::METALLIC);
			if (!metallicMap)
			{
				spdlog::error("Metallic map not found!");
				ASSERT(false);
			}
			else
			{
				spdlog::debug("Name of the metallic map: {}", metallicMap->GetFilePath());
				material->SetMetallicMap(metallicMap);
			}
			auto aoMap = ExtractTexture(i, MaterialMapType::AMBIENTOCCLUSION);
			if (!aoMap)
			{
				spdlog::error("Ambient occlusion map not found!");
				ASSERT(false);
			}
			else
			{
				spdlog::debug("Name of the ambient occlusion map: {}", aoMap->GetFilePath());
				material->SetAmbientOcclusionMap(aoMap);
			}


			//material->SetDiffuseMap(theMesh.m_MaterialMaps[0].mapTexture);
			material->SetShader(theShader);

			m_Meshes[i].AddData(rData, modelMats, material);
			renderablesList.push_back(&m_Meshes[i]);
		}

	}
	
	Models::~Models()
	{
		DELETE(m_TheModel);
		DELETEARRAY(m_Meshes);
	}

	void Models::Init()
	{
	}

	void Models::Update()
	{
	}

	void Models::CleanUp()
	{
	}

	std::shared_ptr<Texture> Models::ExtractTexture(size_t meshIndex, const MaterialMapType & type) const
	{
		ASSERT(meshIndex < m_TheModel->GetMeshList().size());
		const Mesh& theMesh = m_TheModel->GetMeshList()[meshIndex];

		for (const MaterialMap& aMat : theMesh.m_MaterialMaps)
		{
			if (aMat.type == type)
			{
				return aMat.mapTexture;
			}
		}

		return std::shared_ptr<Texture>(nullptr);
	}
}