#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class AppGui
{
public:
	AppGui(GLFWwindow* Window);
	~AppGui();

	// Must be set before the render loop
	void SetFrameBuffer(void* Color);
	void SetAttributes(glm::vec3* CamPosition, glm::vec3* MeshColor, glm::vec3* DirectionalLight);

	void NewFrame();
	void RenderUI();

	// ====== User Interface =====
	void Viewport();
	void Properties();
	void Camera();
	// ====== User Interface =====

private:
	void*		m_FrameBufferColor	= nullptr;
	glm::vec3*	m_CamPosition		= nullptr;
	glm::vec3*	m_MeshColor			= nullptr;
	glm::vec3*	m_DirectionalLight	= nullptr;
};