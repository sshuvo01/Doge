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

		m_VB = std::make_shared<VertexBuffer>(vertices, sizeof(float) * (3 + 3 + 2) * 3 );
		m_VBL = std::make_shared<VertexBufferLayout>();
		m_VBL->Push(3);
		m_VBL->Push(3);
		m_VBL->Push(2);
		m_VAO = std::make_shared<VertexArray>();
		m_VAO->AddBuffer(*m_VB, *m_VBL);
		m_IB = std::make_shared<IndexBuffer>(3);

		glm::mat4 m{ 1.0f };
		m_ModelMats.push_back(m);
		m = glm::translate(m, glm::vec3(1.0f, 1.0f, 0.0f));
		m_ModelMats.push_back(m);

		m_Material = std::make_shared<Material>();
		m_Material->m_DiffuseMap = std::make_shared<Texture>("res/textures/doge.jpg", true);
		m_Material->m_Shader = std::make_shared<Shader>("res/shaders/vert/Test.vert", "res/shaders/frag/Test.frag");
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
