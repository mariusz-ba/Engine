#pragma once

#include "buffers/GLVertexArray.h"
#include "buffers/GLIndexBuffer.h"
#include "Renderable2D.h"
#include "camera/Camera.h"
#include "Shader.h"

#include <glm/glm.hpp>

namespace engine { namespace graphics {

	// Renderer2D is an interface for all 2D renderers. All derived classes
	// decide how all renderable items are stored and printed on the screen.

	class Renderer2D {
	public:
		virtual void push(const glm::mat4& matrix) {}
		virtual void pop() {}

		virtual void begin() {}
		virtual void submit(const Renderable2D* renderable) = 0;
		virtual void end() {}
		virtual void flush() = 0;

		inline void setCamera(Camera* camera) { m_Camera = camera; }
		inline Camera* getCamera() const { return m_Camera; }
		inline void setShader(Shader* shader) { m_Shader = shader; }
		inline Shader* getShader() const { return m_Shader; }
	
	protected:
		Camera* m_Camera;
		Shader* m_Shader;
		std::vector<glm::mat4> m_TransformationStack;
	};

} }