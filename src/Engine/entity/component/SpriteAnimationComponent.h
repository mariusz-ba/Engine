#pragma once

#include "Component.h"
#include "../../graphics/SpriteAnimationMixer.h"
#include <map>

namespace engine { namespace entity { namespace component {

	class SpriteAnimationComponent : public Component {
	public:
		SpriteAnimationComponent(const std::vector<graphics::SpriteAnimation>& anims);
		SpriteAnimationComponent(const std::initializer_list<graphics::SpriteAnimation>& anims);
		SpriteAnimationComponent(graphics::SpriteAnimationMixer* mixer);
		virtual ~SpriteAnimationComponent();

		static ComponentType* getStaticType()
		{
			static ComponentType type({ "SpriteAnimation" });
			return &type;
		}

		inline virtual ComponentType* getType() const override { return getStaticType(); }

	public:
		graphics::SpriteAnimationMixer* mixer;
	};

} } }