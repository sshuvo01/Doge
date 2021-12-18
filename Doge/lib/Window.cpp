#include "Window.h"

namespace doge
{
	inline void processInput(GLFWwindow *window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	// ---------------------------------------------------------------------------------------------
	inline void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}

	//
	Window::Window(uint width, uint height, const std::string& title)
		:m_Width(width), m_Height(height), m_Title(title), m_Window(nullptr)
	{
		SetupWindow();
	}

	Window::~Window()
	{

	}
	void Window::Run() const
	{
		if (!m_Window)
		{
			spdlog::error("Window was not created");
			return;
		}

		while (!glfwWindowShouldClose(m_Window))
		{
			processInput(m_Window);
			
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(m_Window);
			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	/*private functions*/
	int Window::SetupWindow()
	{
		/* Initialize the library */
		if (!glfwInit())
		{
			spdlog::error("Failed to init glfw!");
			return -1;
		}

		/* Create a windowed mode window and its OpenGL context */
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
		if (!m_Window)
		{
			spdlog::error("Failed to create window!");
			glfwTerminate();
			return -1;
		}
		else
		{
			spdlog::debug("Created window. Width: {}, Height: {}, Title: {}", m_Width, m_Height, m_Title);
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(m_Window);

		if (glewInit() != GLEW_OK)
		{
			spdlog::error("Failed to init glew!");
			return -1;
		}

		glfwMakeContextCurrent(m_Window);
		//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		//glfwSetCursorPosCallback(m_Window, mouse_callback);
		//glfwSetScrollCallback(window, scroll_callback);

		// tell GLFW to capture our mouse
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		return 0;
	}


} // end of doge