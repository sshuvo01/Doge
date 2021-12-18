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

unsigned int width = 640 * 2;
unsigned int height = 480 * 2;
doge::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

float lastX = width / 2.0f;
float lastY = height / 2.0f;
bool firstMouse = true;

float vertices[] = {
	   -0.5f, -0.5f, 0.0f, 1.0f, 0.0, 0.0f, 0.0f, 0.0f, // left  
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // right 
		0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f  // top   
};

static void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//glfwSetWindowShouldClose(window, true);
		glfwDestroyWindow(window);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(doge::FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(doge::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(doge::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(doge::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	{

	}
	
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

static int SetupWindow(GLFWwindow*& window, int width, int height, const std::string& title)
{
	//GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		spdlog::critical("Error with GLFW!");
		return -1;
	}

	glfwMakeContextCurrent(window);
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	return 0;
}

class Test
{
public:
	Test() = delete;
	NOCOPYNOASSIGN(Test);
	Test(int x) : m_X(x) { std::cout << m_X << " Test constructed\n"; }
	~Test() { std::cout << m_X << " Test destroyed\n"; }
	void Print() const { std::cout << m_X << std::endl; }
	void Set(int xx) { m_X = xx; }
private:
	int m_X;
};

int mainTest()
{
	std::shared_ptr<Test> st, st3;
	st = std::make_shared<Test>(1);
	{

		std::shared_ptr<Test> st2 = std::make_shared<Test>(23);
		st2->Print();
		st3 = st2;
		std::shared_ptr<Test> aa{ new Test{420} };
		aa->Print();
		st3 = aa;
	}

	st->Print();
	//
	Test aTest{ 1234 };
	const Test* tp;
	tp = &aTest;
	
	std::vector<const Test*> vec;
	vec.push_back(tp);
	vec[0]->Print();

	std::cin.get();
	return 0;
}

int main2()
{
	spdlog::set_level(spdlog::level::debug);
	// 
	//doge::Window theWindow{ width, height, "SSS" };
	GLFWwindow* window;
	int code = SetupWindow(window, width, height, "TEST");
	
	doge::Texture justATexture{ "res/textures/doge.jpg", true };
	doge::Shader testShader{ "res/shaders/vert/Test.vert", "res/shaders/frag/Test.frag" };
	doge::VertexBuffer vb{ vertices, sizeof(float) * (3 + 3 + 2) * 3 };
	doge::VertexBufferLayout vbl;
	vbl.Push(3);
	vbl.Push(3);
	vbl.Push(2);
	doge::VertexArray vao;
	vao.AddBuffer(vb, vbl);
	doge::IndexBuffer ib{ 3 };

	testShader.SetUniform3f("color", { 0.0f, 1.0f, 1.0f });
	testShader.SetUniform1i("uTexture", 0);
	justATexture.Bind(0);
	

	while (!glfwWindowShouldClose(window))
	{
		////////////////////////
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);
		////////////////////////
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(camera.GetViewMatrix());
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);

		glm::mat4 mvp = projection * view * model;

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		testShader.SetUniformMatrix4f("u_Model", model);
		testShader.SetUniformMatrix4f("u_View", view);
		testShader.SetUniformMatrix4f("u_Projection", projection);
		testShader.SetUniformMatrix4f("u_MVP", mvp);

		// draw our first triangle
		//glBindVertexArray(VAO); 
		vao.Bind();
		ib.Bind();

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, NULL);
		//glDrawElements(GLShape, ib.GetCount(), GL_UNSIGNED_INT, nullptr)

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	

	std::cin.get();
	return 0;
}


int main()
{
	spdlog::set_level(spdlog::level::debug);
	// 
	//doge::Window theWindow{ width, height, "SSS" };
	GLFWwindow* window;
	int code = SetupWindow(window, width, height, "TEST");

	doge::Renderer rnder;
	doge::Triangles tri;
	rnder.m_Renderables.push_back(&tri);


	while (!glfwWindowShouldClose(window))
	{
		////////////////////////
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);
		////////////////////////
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(camera.GetViewMatrix());
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);

		glm::mat4 mvp = projection * view * model;

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		rnder.RenderThemAll(camera.GetViewMatrix(), projection);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	std::cin.get();
	return 0;
}
