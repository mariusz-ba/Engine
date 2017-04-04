#include "Scene2D.h"
#include "graphics/BatchRenderer.h"

namespace engine {

	Scene2D::Scene2D(const glm::mat4& projectionMatrix) :
		m_Renderer(new graphics::BatchRenderer()),
		m_Camera(new graphics::Camera(projectionMatrix))
	{
		m_Renderer->setCamera(m_Camera);
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
				animationComponent->animations[animationComponent->currentAnimation].update(deltaTime);
		}
	}

	void Scene2D::onRender()
	{
		// TODO: render only visible entities, split into chunks
		m_Renderer->begin();
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