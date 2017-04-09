#include "BatchRenderer.h"

namespace engine { namespace graphics {

	glm::vec3 operator*(const glm::mat4& matrix, const glm::vec3& vector)
	{
		glm::vec4 vec = matrix * glm::vec4(vector.x, vector.y, vector.z, 1.0);
		return glm::vec3(vec.x, vec.y, vec.z);
	}

	BatchRenderer::BatchRenderer() :
		m_RenderableCount(0)
	{
		init();
		m_TransformationStack.push_back(glm::mat4(1.0f));
	}

	void BatchRenderer::init()
	{
		glCreateVertexArrays(1, &m_VAO);
		glCreateBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glNamedBufferStorage(m_VBO, RENDERER_BUFFER_SIZE, nullptr, GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);

		glVertexArrayVertexBuffer(m_VBO, VERTEX_SHADER_POSITION, m_VBO, 0, RENDERER_VERTEX_SIZE);
		glVertexArrayAttribFormat(m_VBO, VERTEX_SHADER_POSITION, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(m_VBO, VERTEX_SHADER_POSITION, VERTEX_SHADER_POSITION);
		glEnableVertexArrayAttrib(m_VBO, VERTEX_SHADER_POSITION);

		glVertexArrayVertexBuffer(m_VBO, VERTEX_SHADER_COLOR, m_VBO, offsetof(VertexData, color), RENDERER_VERTEX_SIZE);
		glVertexArrayAttribFormat(m_VBO, VERTEX_SHADER_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0);
		glVertexArrayAttribBinding(m_VBO, VERTEX_SHADER_COLOR, VERTEX_SHADER_COLOR);
		glEnableVertexArrayAttrib(m_VBO, VERTEX_SHADER_COLOR);

		glVertexArrayVertexBuffer(m_VBO, VERTEX_SHADER_TEXCOORDS, m_VBO, offsetof(VertexData, texcoords), RENDERER_VERTEX_SIZE);
		glVertexArrayAttribFormat(m_VBO, VERTEX_SHADER_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(m_VBO, VERTEX_SHADER_TEXCOORDS, VERTEX_SHADER_TEXCOORDS);
		glEnableVertexArrayAttrib(m_VBO, VERTEX_SHADER_TEXCOORDS);

		glVertexArrayVertexBuffer(m_VBO, VERTEX_SHADER_TEXSLOT, m_VBO, offsetof(VertexData, ts), RENDERER_VERTEX_SIZE);
		glVertexArrayAttribFormat(m_VBO, VERTEX_SHADER_TEXSLOT, 1, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(m_VBO, VERTEX_SHADER_TEXSLOT, VERTEX_SHADER_TEXSLOT);
		glEnableVertexArrayAttrib(m_VBO, VERTEX_SHADER_TEXSLOT);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint* indices = new GLuint[RENDERER_INDICES_COUNT];

		unsigned int indexes = 0;
		for (unsigned int i = 0; i < RENDERER_INDICES_COUNT; i += 6, indexes += 4)
		{
			// Generate indices
			indices[  i  ] = indexes;
			indices[i + 1] = indexes + 1;
			indices[i + 2] = indexes + 2;
			indices[i + 3] = indexes + 1;
			indices[i + 4] = indexes + 3;
			indices[i + 5] = indexes + 2;
		}

		m_IndexBuffer = new GLIndexBuffer(indices, RENDERER_INDICES_COUNT);

		delete[] indices;
	}

	BatchRenderer::~BatchRenderer()
	{
		m_Shader->disable();
	}

	void BatchRenderer::push(const glm::mat4& matrix)
	{
		m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
	}

	void BatchRenderer::pop()
	{
		if (m_TransformationStack.size() > 1)
			m_TransformationStack.pop_back();
	}

	void BatchRenderer::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_Buffer = (VertexData*)glMapNamedBufferRange(m_VBO, 0, RENDERER_BUFFER_SIZE, GL_MAP_WRITE_BIT);
	}

	void BatchRenderer::submit(const Renderable2D* renderable)
	{
		if (m_RenderableCount >= RENDERER_MAXIMUM_SPRITES) {
			end();
			flush();
			begin();
		}

		const glm::vec3& position = renderable->getPosition();
		const glm::vec2& size = renderable->getSize();
		const glm::vec4& color = renderable->getColor();
		const std::vector<glm::vec2>& uvs = renderable->getTextureCoords();
		GLuint textureID = renderable->getTexture() ? renderable->getTexture()->getTextureID() : 0;

		GLfloat ts = 0.0f;

		unsigned int c = 0;

		if (textureID > 0)
		{
			// render texture
			bool found = false;
			for (int i = 0; i < m_TextureSlots.size(); ++i)
			{
				if (m_TextureSlots[i] == textureID) 
				{
					ts = (GLfloat)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				if (m_TextureSlots.size() >= 32)
				{
					end();
					flush();
					begin();
					m_TextureSlots.clear();
				}
				m_TextureSlots.push_back(textureID);
				ts = (float)(m_TextureSlots.size() - 1);
			}
		}
		else
		{
			// render color
			unsigned int r = color.r * 255;
			unsigned int g = color.g * 255;
			unsigned int b = color.b * 255;
			unsigned int a = color.a * 255;

			c = a << 24 | b << 16 | g << 8 | r;

			//printf("%x\n", c);
		}

		m_Buffer->position = m_TransformationStack.back() * position;
		m_Buffer->color = c;
		m_Buffer->texcoords = uvs[0];
		m_Buffer->ts = ts;
		m_Buffer++;

		m_Buffer->position = m_TransformationStack.back() * glm::vec3(position.x + size.x, position.y, position.z);
		m_Buffer->color = c;
		m_Buffer->texcoords = uvs[1];
		m_Buffer->ts = ts;
		m_Buffer++;

		m_Buffer->position = m_TransformationStack.back() * glm::vec3(position.x, position.y + size.y, position.z);
		m_Buffer->color = c;
		m_Buffer->texcoords = uvs[2];
		m_Buffer->ts = ts;
		m_Buffer++;
		//TODO: zmieniæ - na +
		m_Buffer->position = m_TransformationStack.back() * glm::vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->color = c;
		m_Buffer->texcoords = uvs[3];
		m_Buffer->ts = ts;
		m_Buffer++;

		//glNamedBufferSubData(m_VBO, m_RenderableCount * RENDERER_SPRITE_SIZE, RENDERER_SPRITE_SIZE, &renderable->getData()[0]);
			
		++m_RenderableCount;
	}

	void BatchRenderer::end()
	{
		glUnmapNamedBuffer(m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRenderer::flush()
	{
		for (int i = 0; i < m_TextureSlots.size(); ++i)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
		}

		glBindVertexArray(m_VAO);
		m_IndexBuffer->bind();

		glDrawElements(GL_TRIANGLES, m_RenderableCount * 6, GL_UNSIGNED_INT, 0);

		m_IndexBuffer->unbind();
		glBindVertexArray(0);
		m_RenderableCount = 0;
	}

} }