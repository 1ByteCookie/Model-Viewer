#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(const glm::vec3& Position, const glm::vec3& Target);
	~Camera() = default;

	void LookAt();

	const glm::mat4& GetMatrix() { return m_Matrix; }
	glm::vec3& GetPosition() { return m_Position; }

private:
	glm::mat4	m_Matrix;
	glm::vec3	m_Position;
	glm::vec3	m_Target;
	glm::vec3	m_Up;
};