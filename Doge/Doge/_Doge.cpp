#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Camera.h"
#include "Renderer.h"
#include "Renderables/Triangles.h"
#include "Renderables/Boxes.h"
#include "Renderables/Plane.h"
#include "Engine.h"


int main()
{
	spdlog::set_level(spdlog::level::debug);
	doge::EngineSpec es;
	doge::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	es.camera = &camera;
	doge::Engine::GetInstance().InitEngine(es);

	// renderer
	doge::Renderer rnder;
	doge::Triangles tri;
	doge::Boxes box;
	doge::Scene theScene;
	doge::Plane plane;
	theScene.renderablesList.push_back(&box);
	theScene.renderablesList.push_back(&plane);

	// lights!
	doge::DirectionalLight dLite1{ {1.0f, 6.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f} };
	doge::DirectionalLight dLite2{ {-2.0f, 4.0f, -1.0f}, {0.5f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.2f} };
	theScene.lightsList.push_back(&dLite1);
	theScene.lightsList.push_back(&dLite2);

	//rnder.m_Renderables.push_back(&tri);
	es.renderer = &rnder;
	doge::Engine::GetInstance().SetRenderer(&rnder);
	doge::Engine::GetInstance().SetScene(&theScene);
	doge::Engine::GetInstance().Run();

	std::cin.get();
	return 0;
}

