#include "Entity.h"

namespace engine { namespace entity {

	using namespace component;

	Entity::Entity()
	{
	}

	Entity::Entity(graphics::Sprite* sprite, const glm::mat4& transformation)
	{
		addComponent(new SpriteComponent(sprite));
	}

	Entity::~Entity()
	{
		for (auto it = m_Components.begin(); it != m_Components.end(); ++it)
			delete it->second;
	}

	void Entity::addComponent(component::Component* component)
	{
		m_Components[component->getType()] = component;
	}

} }