#include "GLIndexBuffer.h"

namespace engine { namespace graphics {

	GLIndexBuffer::GLIndexBuffer(GLuint* data, unsigned int count)
		: m_Count(count)
	{
		glCreateBuffers(1, &m_BufferID);
		bind();
		glNamedBufferStorage(m_BufferID, count * sizeof(GLuint), data, GL_DYNAMIC_STORAGE_BIT);
		unbind();
	}

	void GLIndexBuffer::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}

	void GLIndexBuffer::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

} }