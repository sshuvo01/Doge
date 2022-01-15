#include "Engine.h"

namespace doge
{
	Engine::~Engine()
	{
	}

	Engine::Engine()
	{
		spdlog::debug("Singleton engine constructed");
		m_LastX = m_Spec.screenWidth / 2.0;
		m_LastY = m_Spec.screenHeight / 2.0;
	}

	Engine & Engine::GetInstance()
	{
		static Engine instance; 
		return instance;
	}

	void Engine::InitEngine(const EngineSpec & es)
	{
		spdlog::debug("Initializing engine");
		m_Spec = es;
		m_LastX = m_Spec.screenWidth / 2.0;
		m_LastY = m_Spec.screenHeight / 2.0;
		SetupWindow();
	}

	void Engine::Run()
	{
		Validate();
		m_Spec.renderer->SetScene(m_Spec.scene);
		m_Spec.renderer->SetWidth(m_Spec.screenWidth);
		m_Spec.renderer->SetHeight(m_Spec.screenHeight);
		
		//m_Spec.renderer->Set

		spdlog::debug("Entering render loop");
		while (!glfwWindowShouldClose(m_Window))
		{
			CalculateDeltaTime();
			ProcessInput(m_Window);
			//
			
			glm::vec3 campos = m_Spec.camera->Position;
			glm::mat4 projection = glm::perspective(glm::radians(m_Spec.camera->Zoom), (float)m_Spec.screenWidth / (float)m_Spec.screenHeight, 0.1f, 100.0f);
			//m_Spec.renderer->RenderThemAll(m_Spec.camera->GetViewMatrix(), projection);
			m_Spec.renderer->SetProjectionMat(projection);
			m_Spec.renderer->SetViewMat(m_Spec.camera->GetViewMatrix());
			m_Spec.renderer->SetCameraPosition(campos);
			m_Spec.renderer->RenderFrame();

			//
			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}
	}

	int Engine::SetupWindow()
	{
		/* Initialize the library */
		if (!glfwInit())
		{
			spdlog::critical("Failed to init glfw!");
			ASSERT(false);
			return -1;
		}

		/* Create a windowed mode window and its OpenGL context */
		m_Window = glfwCreateWindow(m_Spec.screenWidth , m_Spec.screenHeight, m_Spec.windowTitle.c_str(), NULL, NULL);
		if (!m_Window)
		{
			spdlog::error("Failed to create window!");
			glfwTerminate();
			ASSERT(false);
			return -1;
		}
		else
		{
			spdlog::debug("Created window. Width: {}, Height: {}, Title: {}", m_Spec.screenWidth, m_Spec.screenHeight, m_Spec.windowTitle);
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(m_Window);

		if (glewInit() != GLEW_OK)
		{
			spdlog::error("Failed to init glew!");
			ASSERT(false);
			return -1;
		}

		glfwMakeContextCurrent(m_Window);
		//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(m_Window, MouseCallback);
		glfwSetScrollCallback(m_Window, ScrollCallback);

		// tell GLFW to capture our mouse
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		spdlog::debug("Set up window");
		return 0;
	}

	void Engine::ProcessInput(GLFWwindow * window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			//glfwSetWindowShouldClose(window, true);
			glfwDestroyWindow(window);
		}

		if (!m_Spec.camera)
		{
			spdlog::critical("No camera set");
			ASSERT(false);
		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			//   camera.ProcessKeyboard(doge::FORWARD, deltaTime);
			m_Spec.camera->ProcessKeyboard(doge::FORWARD, m_DeltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			//camera.ProcessKeyboard(doge::BACKWARD, deltaTime);
			m_Spec.camera->ProcessKeyboard(doge::BACKWARD, m_DeltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			//camera.ProcessKeyboard(doge::LEFT, deltaTime);
			m_Spec.camera->ProcessKeyboard(doge::LEFT, m_DeltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			//camera.ProcessKeyboard(doge::RIGHT, deltaTime);
			m_Spec.camera->ProcessKeyboard(doge::RIGHT, m_DeltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		{

		}
	}

	void Engine::CalculateDeltaTime()
	{
		m_CurrentFrameTime = glfwGetTime();
		m_DeltaTime = m_CurrentFrameTime - m_LastFrameTime;
		m_LastFrameTime = m_CurrentFrameTime;
	}

	void Engine::Validate() const
	{
		if (!m_Spec.renderer)
		{
			spdlog::critical("Renderer not set");
			ASSERT(false);
			return;
		}
		if (!m_Spec.camera)
		{
			spdlog::critical("Camera not set");
			ASSERT(false);
			return;
		}
		if (!m_Spec.scene)
		{
			spdlog::critical("Scene not set");
			ASSERT(false);
			return;
		}

	}

	void Engine::MouseCallback_(GLFWwindow * window, double xpos, double ypos)
	{
		if (m_FirstMouse)
		{
			m_LastX = xpos;
			m_LastY = ypos;
			m_FirstMouse = false;
		}

		float xoffset = xpos - m_LastX;
		float yoffset = m_LastY - ypos; // reversed since y-coordinates go from bottom to top

		m_LastX = xpos;
		m_LastY = ypos;

		if (!m_Spec.camera)
		{
			spdlog::critical("Camera not set");
			ASSERT(false);
		}
		m_Spec.camera->ProcessMouseMovement(xoffset, yoffset);
		//camera.ProcessMouseMovement(xoffset, yoffset);
	}

	void Engine::ScrollCallback_(GLFWwindow * window, double xoffset, double yoffset)
	{
		//camera.ProcessMouseScroll(yoffset);
		if (!m_Spec.camera)
		{
			spdlog::critical("Camera not set");
			ASSERT(false);
		}
		m_Spec.camera->ProcessMouseScroll(yoffset);
	}

	//
	void MouseCallback(GLFWwindow * window, double xpos, double ypos)
	{
		Engine::GetInstance().MouseCallback_(window, xpos, ypos);
	}

	void ScrollCallback(GLFWwindow * window, double xoffset, double yoffset)
	{
		Engine::GetInstance().ScrollCallback_(window, xoffset, yoffset);
	}

}

