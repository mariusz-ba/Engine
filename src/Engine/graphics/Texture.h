#pragma once

#include <GL/glew.h>
#include "FreeImage.h"

namespace engine { namespace graphics {

	class Texture {
	public:
		Texture();
		Texture(const char* filename);
		~Texture();

		void bind();
		void unbind();

		void loadFromFile(const char* filename);

		inline GLuint getTextureID() const { return m_TextureID; }
		inline unsigned int getWidth() const { return m_Width; }
		inline unsigned int getHeight() const { return m_Height; }
		inline unsigned int getBitsPerPixel() const { return m_BitsPerPixel; }

		inline void setTextureID(GLuint textureid) { m_TextureID = textureid; }
		inline void setWidth(unsigned int width) { m_Width = width; }
		inline void setHeight(unsigned int height) { m_Height = height; }
		inline void setBitsPerPixel(unsigned int bpp) { m_BitsPerPixel = bpp; }

	protected:
		void load(const char* filename);

	private:
		GLuint m_TextureID;
		unsigned int m_Width;
		unsigned int m_Height;
		unsigned int m_BitsPerPixel;
	};

} }