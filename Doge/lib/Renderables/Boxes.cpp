#include "Boxes.h"
#include "VertexBufferLayout.h"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

namespace doge
{
	Boxes::Boxes()
	{
		float verticesNM[] = {
			// back face
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,  2.0f, 0.0f, 0.0f,  0.0f, 2.0f, 0.0f, // bottom-left
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,  2.0f, 0.0f, 0.0f,  0.0f, 2.0f, 0.0f, // top-right
			 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,  2.0f, 0.0f, 0.0f,  0.0f, 2.0f, 0.0f, // bottom-right         

			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,  2.0f, 0.0f, 0.0f,  0.0f, 2.0f, 0.0f, // top-right
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,  2.0f, 0.0f, 0.0f,  0.0f, 2.0f, 0.0f, // bottom-left
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,  2.0f, 0.0f, 0.0f,  0.0f, 2.0f, 0.0f, // top-left
			// front face
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,  2.0f, 0.0f, 0.0f,  0.0f, 2.0f, 0.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,  2.0f, 0.0f, 0.0f,  0.0f, 2.0f, 0.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,  2.0f, 0.0f, 0.0f,  0.0f, 2.0f, 0.0f, // top-right

			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,  2.0f, 0.0f, 0.0f,  0.0f, 2.0f, 0.0f, // top-right
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,  2.0f, 0.0f, 0.0f,  0.0f, 2.0f, 0.0f, // top-left
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,  2.0f, 0.0f, 0.0f,  0.0f, 2.0f, 0.0f, // bottom-left
			// left face
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 2.0f, 0.0f,  0.0f, 0.0f, -2.0f, // top-right
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,  0.0f, 2.0f, 0.0f,  0.0f, 0.0f, -2.0f, // top-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 2.0f, 0.0f,  0.0f, 0.0f, -2.0f, // bottom-left

			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 2.0f, 0.0f,  0.0f, 0.0f, -2.0f, // bottom-left
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 2.0f, 0.0f,  0.0f, 0.0f, -2.0f, // bottom-right
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 2.0f, 0.0f,  0.0f, 0.0f, -2.0f, // top-right
			// right face
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 2.0f, 0.0f,  0.0f, 0.0f, -2.0f, // top-left
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 2.0f, 0.0f,  0.0f, 0.0f, -2.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,  0.0f, 2.0f, 0.0f,  0.0f, 0.0f, -2.0f, // top-right         

			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 2.0f, 0.0f,  0.0f, 0.0f, -2.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 2.0f, 0.0f,  0.0f, 0.0f, -2.0f, // top-left
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 2.0f, 0.0f,  0.0f, 0.0f, -2.0f, // bottom-left     
			// bottom face
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f, // top-right
			 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f, // top-left
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f, // bottom-left

			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f, // bottom-left
			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f, // bottom-right
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f, // top-right
			// top face
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f, // top-left
			 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f, // top-right     

			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f, // bottom-right
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f, // top-left
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f  // bottom-left
		};

		float vertices[] = {
			// back face
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         

			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
			// front face
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right

			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			// left face
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left

			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			// right face
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         

			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
			// bottom face
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			// top face
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
		};

		/*

		size_t arrayCount = sizeof(vertices) / sizeof(float);
		std::vector<float> verticesVector(arrayCount);
		std::copy(vertices, vertices + arrayCount, verticesVector.begin());
		auto newVec = verticesVector;


		std::vector< glm::vec3 > tempVec3;
		std::vector< glm::vec2 > tempVec2;
		std::vector< std::vector<float>::iterator > tempIt;

		int triangleCounter = 1;
		for (size_t i = 8; i < verticesVector.size(); i+=8)
		{
			glm::vec3 pos = { verticesVector[i - 8], verticesVector[i - 7], verticesVector[i - 6] };
			glm::vec2 uv = { verticesVector[i - 2], verticesVector[i - 1] };

			std::cout << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
			std::cout << uv.x << ", " << uv.y << std::endl;
			//std::cin.get();

			tempVec3.push_back(pos);
			tempVec2.push_back(uv);
			tempIt.push_back(newVec.begin() + i);

			if (tempVec3.size() != 3)
			{
				continue;
			}

			glm::vec3 tangent, bitangent;
			GetTangentBitengent(tempVec3[0], tempVec3[1], tempVec3[2], tempVec2[0], tempVec2[1], tempVec2[2], tangent, bitangent);

			std::cout << "Triangle: " << triangleCounter << ":" << std::endl;
			std::cout << "Tangent: " << "[" << tangent.x << ", " << tangent.y << ", " << tangent.z << "]" << std::endl;
			std::cout << "Bitangent: " << "[" << bitangent.x << ", " << bitangent.y << ", " << bitangent.z << "]" << std::endl;
			std::cout << std::endl;

			triangleCounter++;
			tempVec3.clear();
			tempVec2.clear();
			tempIt.clear();
			//newVec.insert(newVec.begin() + i, 420.0f);
		}


		newVec.push_back(420.0f);
		*/


		//std::cin.get();

		RenderableData rData;
		uint layout[] = { 3, 3, 2, 3, 3 };
		rData.buffer = verticesNM;
		rData.bufferSize = 36 * (3 + 3 + 2 + 3 + 3) * sizeof(float);
		rData.index = nullptr;
		rData.indexCount = 36;
		rData.layoutCount = 5;
		rData.layout = layout;

		std::vector<glm::mat4> modelMats;
		glm::mat4 m{ 1.0f };
		m = glm::rotate(m, glm::radians(45.0f), { 0.0f, 1.0f, 1.0f });
		modelMats.push_back(m);

		m = { 1.0f };
		m = glm::rotate(m, glm::radians(15.0f), { 0.0f, 0.0f, 1.0f });
		m = glm::translate(m, { 0.0f, -2.2f, -2.0f });
		modelMats.push_back(m);

		auto material = std::make_shared<Material>();
		material->SetDiffuseMap(std::make_shared<Texture>("res/textures/doge.jpg", true));
		material->SetNormalMap(std::make_shared<Texture>("res/textures/brickwall_normal.jpg", true));
		material->SetRoughnessMap(std::make_shared<Texture>("res/textures/barren-ground-rock-bl/barren-ground-rock_roughness.png", true));
		material->SetMetallicMap(std::make_shared<Texture>("res/textures/barren-ground-rock-bl/barren-ground-rock_metallic.png", true));
		material->SetAmbientOcclusionMap(std::make_shared<Texture>("res/textures/barren-ground-rock-bl/barren-ground-rock_ao.png", true));
		
		material->SetShader(std::make_shared<Shader>("res/shaders/vert/Test.vert", "res/shaders/frag/Test.frag"));
		
		AddData(rData, modelMats, material);
		spdlog::debug("Created boxes with {} instances", modelMats.size());
		
	}

	Boxes::~Boxes()
	{
	}

	void Boxes::Init()
	{
	}

	void Boxes::Update()
	{
	}

	void Boxes::CleanUp()
	{
	}
	void Boxes::GetTangentBitengent(const glm::vec3& pos1, const glm::vec3& pos2, const glm::vec3& pos3,
		const glm::vec2& uv1, const glm::vec2& uv2, const glm::vec2& uv3, glm::vec3& tangent, glm::vec3& bitangent) const
	{
		glm::vec3 edge1 = pos2 - pos1;
		glm::vec3 edge2 = pos3 - pos1;
		glm::vec2 deltaUV1 = uv2 - uv1;
		glm::vec2 deltaUV2 = uv3 - uv1;

		float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
		std::cout << "f: " << f << std::endl;

		tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

		bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

	}
}