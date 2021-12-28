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
	doge::Scene theScene;
	theScene.renderablesList.push_back(&tri);

	//rnder.m_Renderables.push_back(&tri);
	es.renderer = &rnder;
	doge::Engine::GetInstance().SetRenderer(&rnder);
	doge::Engine::GetInstance().SetScene(&theScene);
	doge::Engine::GetInstance().Run();

	std::cin.get();
	return 0;
}

