#include "Layer.h"

namespace engine { namespace graphics {

	Layer::Layer(Renderer2D* renderer, Shader* shader, const glm::mat4& projectionMatrix) :
		m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
	{
		m_Shader->enable();
		m_Shader->setUniformMat4("pr_matrix", projectionMatrix);
		m_Shader->disable();
	}

	Layer::~Layer()
	{
		// TODO: delete renderer and shader ?
		for (int i = 0; i < m_Renderables.size(); ++i)
			delete m_Renderables[i];
	}

	void Layer::add(Renderable2D* renderable)
	{
		m_Renderables.push_back(renderable);
	}

	void Layer::render()
	{
		m_Shader->enable();
		m_Renderer->begin();
		for (const Renderable2D* renderable : m_Renderables)
			m_Renderer->submit(renderable);
		m_Renderer->end();
		m_Renderer->flush();
		m_Shader->disable();
	}

} }