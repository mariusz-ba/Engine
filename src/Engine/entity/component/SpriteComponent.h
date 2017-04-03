#pragma once

#include "Component.h"
#include "../../graphics/Sprite.h"

namespace engine { namespace entity { namespace component {

	class SpriteComponent : public Component {
	public:
		SpriteComponent(graphics::Sprite* sprite);
		virtual ~SpriteComponent();

		static ComponentType* getStaticType()
		{
			static ComponentType type({ "Sprite" });
			return &type;
		}
		
		inline virtual ComponentType* getType() const override { return getStaticType(); }

	public:
		graphics::Sprite* sprite;
	};

} } }