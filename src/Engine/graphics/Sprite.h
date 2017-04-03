#pragma once

#include "Renderable2D.h"
#include "Texture.h"

namespace engine { namespace graphics {

	class Sprite : public Renderable2D {
	public:
		Sprite(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		Sprite(const glm::vec3& position, const glm::vec2& size, Texture* texture);
	};

} }