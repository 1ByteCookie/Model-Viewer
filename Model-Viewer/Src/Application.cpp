#include "Application.hpp"
#include <iostream>
#include "Renderer.hpp"
#include "AppGui.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

Application Application::Instance;

int Application::OnStart()
{
	glClearColor(0.4f, 0.0f, 1.0f, 1.0f);
	while (!glfwWindowShouldClose(m_Window))
	{
		Renderer::Instance.Clear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();

		AppGui::NewFrame();
		AppGui::RenderUI();

		Renderer::Instance.EndFrame(m_Window);
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

	m_Window = glfwCreateWindow(m_Width, m_Height, "Model Viewer", nullptr, nullptr);
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

	AppGui::Initialize(m_Window);
}

Application::~Application()
{
	AppGui::CleanUp();

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Application::WindowResize(GLFWwindow* Window, int Width, int Height)
{
	glViewport(0, 0, Width, Height);
}