#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "../Shader.h"
#include "../Renderer2D.h"

namespace engine { namespace graphics {

	class Layer {
	public:
		Layer(Renderer2D* renderer, Shader* shader, const glm::mat4& projectionMatrix);
		virtual ~Layer();

		virtual void add(Renderable2D* renderable);
		virtual void render();

	protected:
		Renderer2D* m_Renderer;
		std::vector<Renderable2D*> m_Renderables;
		Shader* m_Shader;
		glm::mat4 m_ProjectionMatrix;
	};

} }