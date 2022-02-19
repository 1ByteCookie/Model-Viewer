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

	GLuint VAO, VBO, IBO; {

		float VertexData[] = {
			-1.0f, -1.0f,	0.0f, 0.0f,
			-1.0f,  1.0f,	0.0f, 1.0f,
			 1.0f,  1.0f,	1.0f, 1.0f,
			 1.0f, -1.0f,	1.0f, 0.0f
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

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}

	TEXTURE_DESC Descriptor{};
	Descriptor.Path			= "Res/Textures/Cyberpunk2077.png";
	Descriptor.FlipImage	= true;
	Descriptor.Slot			= 8;
	Texture texture(Descriptor);
	
	Shader ShaderProgram("Res/Shaders/Vertex.glsl", "Res/Shaders/Pixel.glsl");
	ShaderProgram.Uniform1i("TextureSampler", texture.Descriptor().Slot);
	ShaderProgram.UniformMatrix4fv("Projection", Projection);
	ShaderProgram.UniformMatrix4fv("Model", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

	Camera MainCamera(glm::vec3(2.5f, 3.0f, 2.f), glm::vec3(0.0f, 0.0f, 0.0f));

	glClearColor(0.4f, 0.0f, 1.0f, 1.0f);
	while (!glfwWindowShouldClose(m_Window))
	{
		glfwPollEvents();

		MainCamera.LookAt();
		ShaderProgram.UniformMatrix4fv("View", MainCamera.GetMatrix());

		RenderTarget.Bind();
		
		Renderer::Instance.Clear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
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