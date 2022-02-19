#include "Application.hpp"
#include <iostream>
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Framebuffer.hpp"
#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Application Application::Instance;

int Application::OnStart()
{
	Framebuffer RenderTarget(0, m_Width, m_Height);
	m_Gui->SetFrameBuffer((void*)RenderTarget.GetColor()->GetID());

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)m_Width/m_Height, 0.01f, 100.0f);
	Camera MainCamera(glm::vec3(10.0f, 10.0f, 20.0f), glm::vec3(0.0f, 0.0f, -5.0f));

	Model Foo("Res/Models/Suzanne/Suzanne.obj");
	Shader FooShader("Res/Shaders/Vertex.glsl", "Res/Shaders/Pixel.glsl");
	FooShader.UniformMatrix4fv("Projection", Projection);
	FooShader.UniformMatrix4fv("View", MainCamera.GetMatrix());
	FooShader.UniformMatrix4fv("Model", glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f) ) );

	glClearColor(0.4f, 0.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST); glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(m_Window))
	{
		glfwPollEvents();

		MainCamera.LookAt();

		RenderTarget.Bind();
		
		Renderer::Instance.Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Renderer::Instance.Draw(Foo, FooShader);

		RenderTarget.Unbind();

		m_Gui->NewFrame();
		m_Gui->RenderUI();

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

	m_Gui = std::make_unique<AppGui>(m_Window);
}

Application::~Application()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Application::WindowResize(GLFWwindow* Window, int Width, int Height)
{
	glViewport(0, 0, Width, Height);
}