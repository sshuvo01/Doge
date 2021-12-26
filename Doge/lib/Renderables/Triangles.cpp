#include "Triangles.h"
#include "VertexBufferLayout.h"
#include <glm/gtc/matrix_transform.hpp>

namespace doge
{
	Triangles::Triangles()
	{
		float vertices[] = 
		{
		   -0.5f, -0.5f, 0.0f, 1.0f, 0.0, 0.0f, 0.0f, 0.0f, // left  
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // right 
			0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f  // top   
		};

		uint layout[] = { 3, 3, 2 };
		RenderableData rData;
		rData.buffer = vertices;
		rData.bufferSize = sizeof(float) * (3 + 3 + 2) * 3;
		rData.indexCount = 3;
		rData.layout = layout;
		rData.layoutCount = 3;
		
		std::vector<glm::mat4> modelMats;
		glm::mat4 m{ 1.0f };
		modelMats.push_back(m);
		m = glm::translate(m, glm::vec3(1.0f, 1.0f, 0.0f));
		modelMats.push_back(m);
		m = glm::translate(m, glm::vec3(-3.0f, 0.0f, 1.0f));
		modelMats.push_back(m);
		m = glm::translate(m, glm::vec3(0.0f, -2.0f, 1.0f));
		modelMats.push_back(m);
		
		AddData(rData, modelMats);


		auto material = std::make_shared<Material>();
		//material->sm_DiffuseMap = std::make_shared<Texture>("res/textures/doge.jpg", true);
		material->SetDiffuseMap(std::make_shared<Texture>("res/textures/doge.jpg", true));
		material->SetShader(std::make_shared<Shader>("res/shaders/vert/Test.vert", "res/shaders/frag/Test.frag"));
		SetMaterial(material);
		//m_Material->m_Shader = std::make_shared<Shader>("res/shaders/vert/Test.vert", "res/shaders/frag/Test.frag");
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
