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
		size_t arrayCount = sizeof(vertices) / sizeof(float);
		std::vector<float> verticesVector(arrayCount);
		std::copy(vertices, vertices + arrayCount, verticesVector.begin());

		RenderableData rData;
		uint layout[] = { 3, 3, 2 };
		rData.buffer = &verticesVector[0];
		rData.bufferSize = 36 * (3 + 3 + 2) * sizeof(float);
		rData.index = nullptr;
		rData.indexCount = 36;
		rData.layoutCount = 3;
		rData.layout = layout;

		std::vector<glm::mat4> modelMats;
		glm::mat4 m{ 1.0f };
		m = glm::rotate(m, glm::radians(45.0f), { 0.0f, 1.0f, 1.0f });
		modelMats.push_back(m);

		//std::cout << verticesVector.size() << "..." << std::endl;
		//std::cin.get();
		/*
		
		m = glm::translate(m, { 0.0f, 0.0f, -6.0f });
		modelMats.push_back(m);
		m = glm::translate(m, { -6.0f, 0.0f, 1.0f });
		modelMats.push_back(m);
		m = glm::translate(m, { -6.0f, 1.0f, 1.0f });
		modelMats.push_back(m);
		m = glm::translate(m, { -3.0f, 1.0f, 2.0f });
		modelMats.push_back(m);

		m = glm::translate(m, { 0.0f, -3.4f, 1.0f });
		m = glm::rotate(m, glm::radians(25.0f), { 1.0f, 1.0f, 0.0f });
		modelMats.push_back(m);
		
		m = { 1.0f };
		m = glm::scale(m, { 1.5f, 1.5f, 1.5f });
		m = glm::translate(m, { 4.0f, -1.4f, 1.0f });
		m = glm::rotate(m, glm::radians(55.0f), { 0.0f, 1.0f, 0.0f });
		modelMats.push_back(m);
		m = glm::translate(m, { 0.0f, 3.4f, 0.0f });
		modelMats.push_back(m);
		*/

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