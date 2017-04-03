#include "Sprite.h"

namespace engine { namespace graphics {

	Sprite::Sprite(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) :
		Renderable2D(position, size, color, nullptr)
	{}

	Sprite::Sprite(const glm::vec3& position, const glm::vec2& size, Texture* texture) :
		Renderable2D(position, size, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), texture)
	{}

} }