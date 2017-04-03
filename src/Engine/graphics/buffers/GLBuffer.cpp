#include "GLBuffer.h"

namespace engine { namespace graphics {

	GLBuffer::GLBuffer(GLfloat* data, unsigned int size, unsigned int componentCount)
		: m_ComponentCount(componentCount)
	{
		glCreateBuffers(1, &m_BufferID);
		bind();
		glNamedBufferStorage(m_BufferID, size * sizeof(GLfloat), data, GL_DYNAMIC_STORAGE_BIT);
		unbind();
	}

	void GLBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void GLBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

} }