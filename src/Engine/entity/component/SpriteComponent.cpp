#include "SpriteComponent.h"

namespace engine { namespace entity { namespace component {

	SpriteComponent::SpriteComponent(graphics::Sprite* sprite) :
		sprite(sprite)
	{
	}

	SpriteComponent::~SpriteComponent()
	{
		// TODO: delete it or no ?
		delete sprite;
	}

} } }