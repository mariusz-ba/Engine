#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"
#include <iostream>

namespace engine { namespace graphics {

	struct VertexData {
		glm::vec3 position;		// position
		unsigned int color;		// color
		glm::vec2 texcoords;	// texture coords (uv)
		GLfloat ts;				// texture slot
	};

	class Renderable2D {
	public:
		Renderable2D(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, Texture* texture = nullptr)
			: m_Position(position), m_Size(size), m_Color(color), m_TextureRect(0, 0, size.x, size.y), m_Texture(texture)
		{
			updateTextureCoordsArray();
		}

		inline void setPosition(const glm::vec3& position) { m_Position = position; }
		inline void setSize(const glm::vec2& size) { m_Size = size; };
		inline void setColor(const glm::vec4& color) { m_Color = color; }

		inline const glm::vec3& getPosition() const { return m_Position; }
		inline const glm::vec2& getSize() const { return m_Size; }
		inline const glm::vec4& getColor() const { return m_Color; }
		inline const glm::vec4& getTextureRect() const { return m_TextureRect; }

		inline virtual void move(const glm::vec3& offset) { m_Position += offset;  }

		inline void setTexture(Texture* texture) { m_Texture = texture; }
		inline const Texture* getTexture() const { return m_Texture; }

		inline void setTextureRect(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
			m_TextureRect = glm::vec4(x, y, width, height);
			updateTextureCoordsArray();
		}

		inline void updateTextureCoordsArray() {
			m_TextureCoords.clear();
			glm::vec2 texsize;
			if (!m_Texture)
				texsize = glm::vec2(m_Size.x, m_Size.y);
			else
				texsize = texsize = glm::vec2(m_Texture->getWidth(), m_Texture->getHeight());

			m_TextureCoords.push_back(glm::vec2(m_TextureRect.x / (GLfloat)texsize.x, 1 - (GLfloat)m_TextureRect.y / texsize.y));
			m_TextureCoords.push_back(glm::vec2((m_TextureRect.x + m_TextureRect.z) / (GLfloat)texsize.x, 1 - (GLfloat)m_TextureRect.y / texsize.y));
			m_TextureCoords.push_back(glm::vec2(m_TextureRect.x / (GLfloat)texsize.x, 1 - (GLfloat)(m_TextureRect.y + m_TextureRect.w) / texsize.y));
			m_TextureCoords.push_back(glm::vec2((m_TextureRect.x + m_TextureRect.z) / (GLfloat)texsize.x, 1 - (GLfloat)(m_TextureRect.y + m_TextureRect.w) / texsize.y));
		}
		inline const std::vector<glm::vec2>& getTextureCoords() const { return m_TextureCoords; }

	private:
		glm::vec3 m_Position;
		glm::vec2 m_Size;
		glm::vec4 m_Color;
		glm::vec4 m_TextureRect;
		std::vector<glm::vec2> m_TextureCoords;
		Texture* m_Texture = nullptr;
	};

} }