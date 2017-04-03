#pragma once

#include <unordered_map>
#include "component/Component.h"
#include "component/SpriteComponent.h"
#include "../graphics/Sprite.h"

namespace engine { namespace entity {

	class Entity {
	public:
		Entity();
		Entity(graphics::Sprite* sprite, const glm::mat4& transformation = glm::mat4());
		virtual ~Entity();

		virtual void addComponent(component::Component* component);

		template <typename T>
		const T* getComponent() const
		{
			return getComponentInternal<T>();
		}

		template <typename T>
		T* getComponent()
		{
			return (T*)getComponentInternal<T>();
		}
	private:
		template <typename T>
		const T* getComponentInternal() const
		{
			component::ComponentType* type = T::getStaticType();
			auto it = m_Components.find(type);
			if (it == m_Components.end())
				return nullptr;
			return (T*)it->second;
		}
	protected:
		std::unordered_map<component::ComponentType*, component::Component*> m_Components;
	};

} }