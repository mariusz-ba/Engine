#pragma once

#include "Component.h"
#include "../../graphics/SpriteAnimation.h"
#include <map>

namespace engine { namespace entity { namespace component {

	class SpriteAnimationComponent : public Component {
	public:
		SpriteAnimationComponent(const std::vector<graphics::SpriteAnimation>& animations);
		SpriteAnimationComponent(const std::initializer_list<graphics::SpriteAnimation>& animations);
		virtual ~SpriteAnimationComponent();

		static ComponentType* getStaticType()
		{
			static ComponentType type({ "SpriteAnimation" });
			return &type;
		}

		inline virtual ComponentType* getType() const override { return getStaticType(); }

	public:
		std::map<std::string, graphics::SpriteAnimation> animations;
		std::string currentAnimation;
	};

} } }
// TODO: remove steady_clock::time_point from SpriteAnimation and replace it with update(time) function which takes delta time as input parameter
/*

Entity* entity;

std::string current_animation = entity->getComponent(component::SpriteAnimationComponent>()->currentAnimation;

Scene -> OnUpdate()
entity->getComponent(component::SpriteAnimationComponent>()->animations[currentAnimation].update(deltatime);



*/