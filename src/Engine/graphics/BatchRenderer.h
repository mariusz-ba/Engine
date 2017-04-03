#pragma once

#include "Renderer2D.h"
#include "Renderable2D.h"

#include "buffers/GLBuffer.h"
#include "buffers/GLIndexBuffer.h"
#include "buffers/GLVertexArray.h"

namespace engine { namespace graphics {

#define VERTEX_SHADER_POSITION	0
#define VERTEX_SHADER_COLOR		1
#define VERTEX_SHADER_TEXCOORDS	2
#define VERTEX_SHADER_TEXSLOT	3

#define RENDERER_MAXIMUM_SPRITES	60000
#define RENDERER_VERTEX_SIZE		sizeof(VertexData)
#define RENDERER_SPRITE_SIZE		RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE		RENDERER_SPRITE_SIZE * RENDERER_MAXIMUM_SPRITES
#define RENDERER_INDICES_COUNT		RENDERER_MAXIMUM_SPRITES * 6

	class BatchRenderer : public Renderer2D {
	public:
		BatchRenderer();
		~BatchRenderer();

		virtual void push(const glm::mat4& matrix) override;
		virtual void pop() override;

		virtual void begin() override;
		virtual void submit(const Renderable2D* renderable) override;
		virtual void end() override;
		virtual void flush() override;

		inline GLuint getBuffer() const { return m_VBO; }
	private:
		void init();

	private:
		GLuint m_VAO;
		GLuint m_VBO;
		VertexData* m_Buffer;
		GLIndexBuffer* m_IndexBuffer;
		unsigned short m_RenderableCount;

		std::vector<GLuint> m_TextureSlots;
	};

} }