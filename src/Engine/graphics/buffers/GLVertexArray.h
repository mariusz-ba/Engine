#pragma once

#include "GLBuffer.h"
#include <vector>

namespace engine { namespace graphics {

	class GLVertexArray {
	public:
		GLVertexArray();
		~GLVertexArray();

		void bind();
		void unbind();

		void addBuffer(GLBuffer* buffer, unsigned int index);
	private:
		GLuint m_VertexArrayID;
		std::vector<GLBuffer*> m_Buffers;
	};

} }