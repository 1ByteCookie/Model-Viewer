#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& Position, const glm::vec3& Target)
{
	m_Matrix	= glm::mat4(1.0f);
	m_Position	= Position;
	m_Target	= Target;
	m_Up		= glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::LookAt()
{
	m_Matrix = glm::lookAt(m_Position, m_Target, m_Up);
}
