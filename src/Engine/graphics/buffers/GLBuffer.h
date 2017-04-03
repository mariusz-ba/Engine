#pragma once

#include <GL/glew.h>

namespace engine { namespace graphics {

	class GLBuffer {
	public:
		GLBuffer(GLfloat* data, unsigned int size, unsigned int componentCount);

		void bind();
		void unbind();

		inline unsigned int getComponentCount() const { return m_ComponentCount; }
		inline GLuint getBufferID() const { return m_BufferID; }
	private:
		GLuint m_BufferID;
		unsigned int m_ComponentCount;
	};

} }