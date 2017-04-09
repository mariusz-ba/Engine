#include "Scene2D.h"
#include "graphics/BatchRenderer.h"
#include <numeric>

namespace engine {

	Scene2D::Scene2D(const glm::mat4& projectionMatrix) :
		m_Renderer(new graphics::BatchRenderer()),
		m_Camera(new graphics::Camera(projectionMatrix))
	{
		m_Renderer->setCamera(m_Camera);
		m_Renderer->setShader(new graphics::Shader("shaders/vertex_shader.vert", "shaders/fragment_shader.frag"));
		//m_Renderer->getShader()->enable();

		GLint textIDs[32];
		std::iota(textIDs, textIDs + 32, 0);
		m_Renderer->getShader()->setUnifrom1iv("sampler", textIDs, 32);

		//m_Renderer->getShader()->disable();
	}

	Scene2D::~Scene2D()
	{
		for (int i = 0; i < m_Entities.size(); ++i)
			delete m_Entities[i];
	}

	void Scene2D::add(Entity* entity)
	{
		m_Entities.push_back(entity);
	}

	void Scene2D::onUpdate(float deltaTime)
	{
		// TODO: Do it only for entities that have animations
		for (Entity* entity : m_Entities)
		{
			component::SpriteAnimationComponent* animationComponent = entity->getComponent<component::SpriteAnimationComponent>();
			if (animationComponent)
				animationComponent->mixer->update(deltaTime);
		}
	}

	void Scene2D::onRender()
	{
		// TODO: render only visible entities, split into chunks
		m_Renderer->begin();

		// TODO: move it somewhere xd
		m_Renderer->getShader()->setUniformMat4("pr_matrix", m_Camera->getProjectionMatrix());
		m_Renderer->getShader()->setUniformMat4("vw_matrix", m_Camera->getViewMatrix());

		for (Entity* entity : m_Entities)
		{
			component::SpriteComponent* spriteComponent = entity->getComponent<component::SpriteComponent>();
			if (spriteComponent)
			{
				component::TransformComponent* transformComponent = entity->getComponent<component::TransformComponent>();
				if (transformComponent) m_Renderer->push(transformComponent->transformation);
				m_Renderer->submit(spriteComponent->sprite);
				if (transformComponent) m_Renderer->pop();
			}
		}
		m_Renderer->end();
		m_Renderer->flush();
	}

}