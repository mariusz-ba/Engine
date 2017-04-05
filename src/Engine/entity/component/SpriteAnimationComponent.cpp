#include "SpriteAnimationComponent.h"

namespace engine { namespace entity { namespace component {

	SpriteAnimationComponent::SpriteAnimationComponent(const std::vector<graphics::SpriteAnimation>& animations)
		: mixer(new graphics::SpriteAnimationMixer(animations))
	{
	}

	SpriteAnimationComponent::SpriteAnimationComponent(const std::initializer_list<graphics::SpriteAnimation>& animations)
		: mixer(new graphics::SpriteAnimationMixer(animations))
	{
	}

	SpriteAnimationComponent::SpriteAnimationComponent(graphics::SpriteAnimationMixer* mixer)
		: mixer(mixer)
	{
	}

	SpriteAnimationComponent::~SpriteAnimationComponent()
	{

	}

} } }