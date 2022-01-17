#include "Plane.h"
#include "VertexBufferLayout.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace doge
{
	Plane::Plane()
	{
		float verticesNM[] = 
		{
			// positions            // normals         // texcoords
			 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f,
			-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f,
			-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f,

			 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f,
			-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f,
			 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f,  2.0f, 0.0f, 0.0f,  0.0f, 0.0f, -2.0f
		};

		float vertices[] = {
			// positions            // normals         // texcoords
			 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
			-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
			-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

			 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
			-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
			 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
		};

		unsigned int layout[] = { 3, 3, 2, 3, 3 };
		RenderableData rData;
		rData.buffer = verticesNM;
		rData.bufferSize = 6 * (3 + 3 + 2 + 3 + 3) * sizeof(float);
		rData.index = nullptr;
		rData.indexCount = 6;
		rData.layout = layout;
		rData.layoutCount = 5;
		

		std::vector<glm::mat4> modelMats;
		glm::mat4 m{ 1.0f };
		
		m = glm::translate(m, { 0.0f, -3.2f, 0.f });
		modelMats.push_back(m);
		
		auto material = std::make_shared<Material>();
		material->SetDiffuseMap(std::make_shared<Texture>("res/textures/wall.jpg", true));
		material->SetNormalMap(std::make_shared<Texture>("res/textures/brickwall_normal.jpg", true));
		material->SetShader(std::make_shared<Shader>("res/shaders/vert/Test.vert", "res/shaders/frag/Test.frag"));

		AddData(rData, modelMats, material);
		spdlog::debug("Created planes with {} instances", modelMats.size());
	}

	Plane::~Plane()
	{
	}

	void Plane::Init()
	{
	}

	void Plane::Update()
	{
	}

	void Plane::CleanUp()
	{
	}

	void Plane::GetTangentBitengent(const glm::vec3 & pos1, const glm::vec3 & pos2, const glm::vec3 & pos3, const glm::vec2 & uv1, const glm::vec2 & uv2, const glm::vec2 & uv3, glm::vec3 & tangent, glm::vec3 & bitangent) const
	{
		glm::vec3 edge1 = pos2 - pos1;
		glm::vec3 edge2 = pos3 - pos1;
		glm::vec2 deltaUV1 = uv2 - uv1;
		glm::vec2 deltaUV2 = uv3 - uv1;

		float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

		bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	}
}