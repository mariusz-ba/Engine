#include "Camera.h"

namespace engine { namespace graphics {

	Camera::Camera(const glm::mat4& projectionMatrix) :
		m_ProjectionMatrix(projectionMatrix),
		m_ViewMatrix(glm::mat4())
	{
	}

} }