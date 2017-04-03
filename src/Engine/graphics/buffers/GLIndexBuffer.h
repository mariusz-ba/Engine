#pragma once

#include <GL/glew.h>

namespace engine { namespace graphics {

	class GLIndexBuffer {
	public:
		GLIndexBuffer(GLuint* data, unsigned int count);

		void bind();
		void unbind();

		inline unsigned int getIndicesCount() const { return m_Count; }
		inline GLuint getBufferID() const { return m_BufferID; }

	private:
		GLuint m_BufferID;
		unsigned int m_Count;
	};

} }