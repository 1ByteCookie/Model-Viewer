#include "Renderer.hpp"

Renderer Renderer::Instance;

Renderer::Renderer()
	:m_DeltaTime(0), m_CurrentFrame(0), m_PreviousFrame(0)
{

}

void Renderer::Clear(unsigned int Mask)
{
	glClear(Mask);
}

void Renderer::EndFrame(GLFWwindow* Window)
{
	m_CurrentFrame		= glfwGetTime();
	m_DeltaTime			= m_CurrentFrame - m_PreviousFrame;
	m_PreviousFrame		= m_CurrentFrame;

	glfwSwapBuffers(Window);
}

void Renderer::Draw(Model& model, Shader& shader)
{
	shader.Bind();
	for (unsigned int i = 0; i < model.GetMeshes().size(); i++)
	{
		model.GetMeshes()[i].Bind();
		glDrawElements(GL_TRIANGLE_STRIP, model.GetMeshes()[i].GetIndexCount(), GL_UNSIGNED_INT, nullptr);
	}
}
