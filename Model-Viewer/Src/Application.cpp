#include "Application.hpp"
#include <iostream>
#include "Renderer.hpp"
#include "AppGui.hpp"
#include "Shader.hpp"

Application Application::Instance;

int Application::OnStart()
{
	GLuint VAO, VBO, IBO; {

		float VertexData[] = {
			-0.5f, -0.5f,
			-0.5f,  0.5f,
			 0.5f,  0.5f,
			 0.5f, -0.5f
		};

		unsigned int IndexData[] = {
			0, 1, 2,
			2, 3, 0
		};

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexData), IndexData, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(0);
	}

	Shader ShaderProgram("Res/Shaders/Vertex.glsl", "Res/Shaders/Pixel.glsl");
	ShaderProgram.Bind();

	glClearColor(0.4f, 0.0f, 1.0f, 1.0f);
	while (!glfwWindowShouldClose(m_Window))
	{
		Renderer::Instance.Clear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();

		AppGui::NewFrame();
		AppGui::RenderUI();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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