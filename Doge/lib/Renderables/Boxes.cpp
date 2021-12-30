#include "Boxes.h"
#include "VertexBufferLayout.h"
#include <glm/gtc/matrix_transform.hpp>

namespace doge
{
	Boxes::Boxes()
	{
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		RenderableData rData;
		uint layout[] = { 3, 2 };
		rData.buffer = vertices;
		rData.bufferSize = 36 * (3 + 2) * sizeof(float);
		rData.index = nullptr;
		rData.indexCount = 36;
		rData.layoutCount = 2;
		rData.layout = layout;

		std::vector<glm::mat4> modelMats;
		glm::mat4 m{ 1.0f };
		modelMats.push_back(m);
		m = glm::translate(m, { 0.0f, 0.0f, -3.0f });
		modelMats.push_back(m);
		m = glm::translate(m, { -3.0f, 0.0f, 1.0f });
		modelMats.push_back(m);
		m = glm::translate(m, { 0.0f, -2.0f, 1.0f });
		m = glm::rotate(m, glm::radians(25.0f), { 1.0f, 1.0f, 0.0f });
		modelMats.push_back(m);

		auto material = std::make_shared<Material>();
		material->SetDiffuseMap(std::make_shared<Texture>("res/textures/doge.jpg", true));
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
}