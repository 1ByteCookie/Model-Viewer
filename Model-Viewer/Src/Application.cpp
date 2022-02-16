#include "Application.hpp"
#include <iostream>

Application Application::Instance;

int Application::OnStart()
{
	glClearColor(0.4f, 0.0f, 1.0f, 1.0f);
	while (!glfwWindowShouldClose(m_Window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		
		glfwSwapBuffers(m_Window);
	}

	return 0;
}

Application::Application()
	:m_Window(NULL), m_Width(1600), m_Height(900)
{
	if (!glfwInit())
	{
		std::cout << "Error::\t GLFW" << std::endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(m_Width, m_Height, "Scene", nullptr, nullptr);
	if (!m_Window)
	{
		std::cout << "Error::\t Window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_Window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error::\t GLAD" << std::endl;
		glfwTerminate();
	}

	glfwSetWindowSizeCallback(m_Window, Application::WindowResize);
	std::cout << glGetString(GL_VERSION) << std::endl
		<< glGetString(GL_RENDERER) << std::endl;
}

Application::~Application()
{
}

void Application::WindowResize(GLFWwindow* Window, int Width, int Height)
{
	glViewport(0, 0, Width, Height);
}