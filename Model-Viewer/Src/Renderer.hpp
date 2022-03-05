#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Model.hpp"
#include "Shader.hpp"

class Renderer
{
public:
	// singleton design, used to access member methods. e.g Renderer::Instance.Clear();
	static Renderer Instance;

	void Clear(unsigned int Mask);
	void EndFrame(GLFWwindow* Window);

	void Draw(Model& model, Shader& shader);

	inline float GetDeltaTime() { return m_DeltaTime; }

private:
	Renderer();
	~Renderer() = default;

	float			m_DeltaTime;
	float			m_CurrentFrame;
	float			m_PreviousFrame;
};