#include "Triangles.h"
#include "VertexBufferLayout.h"
#include <glm/gtc/matrix_transform.hpp>

namespace doge
{
	Triangles::Triangles()
	{
		float vertices[] = 
		{
		   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // left  
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // right 
			0.0f,  0.5f, 0.0f, 0.5f, 1.0f  // top   
		};

		uint layout[] = { 3, 2 };
		RenderableData rData;
		rData.buffer = vertices;
		rData.bufferSize = sizeof(float) * (3 + 2) * 3;
		rData.indexCount = 3;
		rData.layout = layout;
		rData.layoutCount = 2;
		
		std::vector<glm::mat4> modelMats;
		glm::mat4 m{ 1.0f };
		modelMats.push_back(m);
		m = glm::translate(m, { 0.0f, 0.0f, -3.0f });
		modelMats.push_back(m);
		m = glm::translate(m, { -3.0f, 0.0f, 1.0f });
		modelMats.push_back(m);
		m = glm::translate(m, { 0.0f, -2.0f, 1.0f });
		modelMats.push_back(m);
		
		auto material = std::make_shared<Material>();
		material->SetDiffuseMap(std::make_shared<Texture>("res/textures/doge.jpg", true));
		material->SetShader(std::make_shared<Shader>("res/shaders/vert/Test.vert", "res/shaders/frag/Test.frag"));
		
		AddData(rData, modelMats, material);
	}

	Triangles::~Triangles()
	{

	}

	void Triangles::Init()
	{

	}

	void Triangles::Update()
	{

	}

	void Triangles::CleanUp()
	{

	}
}
