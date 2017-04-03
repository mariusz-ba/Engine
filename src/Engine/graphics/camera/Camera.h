#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace engine { namespace graphics {

	class Camera {
	public:
		Camera(const glm::mat4& projectionMatrix);

		virtual void Focus() {}
		virtual void Update() {}

		inline void setPosition(const glm::vec3& position) { m_Position = position; }
		inline void setRotation(const glm::vec3& rotation) { m_Rotation = rotation; }
		inline void setProjectionMatrix(const glm::mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }

		inline const glm::vec3& getPosition() const { return m_Position; }
		inline const glm::vec3& getRotation() const { return m_Rotation; }
		inline const glm::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& getViewMatrix() const { return m_ViewMatrix; }

		inline void translate(const glm::vec3& translation) {
			m_Position += translation;
			m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position);
		}
		inline void translate(float x, float y, float z) { translate(glm::vec3(x, y, z)); }

		inline void rotate(const glm::vec3& rotation) {
			m_Rotation += rotation;
			m_ViewMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
			m_ViewMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0));
			m_ViewMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1));
		}
		inline void rotate(float x, float y, float z) { rotate(glm::vec3(x, y, z)); }

	protected:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::vec3 m_Position = glm::vec3(0, 0, 0);
		glm::vec3 m_Rotation;
	};

} }