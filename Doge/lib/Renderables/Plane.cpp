#include "Plane.h"
#include "VertexBufferLayout.h"
#include <glm/gtc/matrix_transform.hpp>

namespace doge
{
	Plane::Plane()
	{
		float vertices[] = {
			// positions            // normals         // texcoords
			 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
			-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
			-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

			 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
			-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
			 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
		};
		unsigned int layout[] = { 3, 3, 2 };
		RenderableData rData;
		rData.buffer = vertices;
		rData.bufferSize = 6 * (3 + 3 + 2) * sizeof(float);
		rData.index = nullptr;
		rData.indexCount = 6;
		rData.layout = layout;
		rData.layoutCount = 3;
		

		std::vector<glm::mat4> modelMats;
		glm::mat4 m{ 1.0f };
		
		m = glm::translate(m, { 0.0f, -3.2f, 0.f });
		modelMats.push_back(m);
		
		auto material = std::make_shared<Material>();
		material->SetDiffuseMap(std::make_shared<Texture>("res/textures/wall.jpg", true));
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
}