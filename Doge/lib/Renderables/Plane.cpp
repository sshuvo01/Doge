#include "Plane.h"
#include "VertexBufferLayout.h"
#include <glm/gtc/matrix_transform.hpp>

namespace doge
{
	Plane::Plane()
	{
		float vertices[] = {
			-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,

			-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
			 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,  1.0f, 1.0f
		};
		unsigned int layout[] = { 3, 2 };
		RenderableData rData;
		rData.buffer = vertices;
		rData.bufferSize = 6 * (3 + 2) * sizeof(float);
		rData.index = nullptr;
		rData.indexCount = 6;
		rData.layout = layout;
		rData.layoutCount = 2;
		

		std::vector<glm::mat4> modelMats;
		glm::mat4 m{ 1.0f };
		m = glm::scale(m, { 10.0f, 10.0f, 10.0f });
		m = glm::rotate(m, glm::radians(90.0f), { 1.0f, 0.0f, 0.0f });
		m = glm::translate(m, { 0.0f, 0.0f, 0.3f });
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