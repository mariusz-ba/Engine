#include "GLVertexArray.h"

namespace engine { namespace graphics {

	GLVertexArray::GLVertexArray()
	{
		glCreateVertexArrays(1, &m_VertexArrayID);
	}

	GLVertexArray::~GLVertexArray()
	{
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void GLVertexArray::bind()
	{
		glBindVertexArray(m_VertexArrayID);
	}

	void GLVertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	void GLVertexArray::addBuffer(GLBuffer* buffer, unsigned int index)
	{
		bind();
		buffer->bind();
		glVertexArrayVertexBuffer(m_VertexArrayID, index, buffer->getBufferID(), 0, sizeof(GLfloat) * buffer->getComponentCount());
		glVertexArrayAttribFormat(m_VertexArrayID, index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(m_VertexArrayID, index, index);
		glEnableVertexArrayAttrib(m_VertexArrayID, index);
		buffer->unbind();
		unbind();

		m_Buffers.push_back(buffer);
	}

} }