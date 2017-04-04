#include "SpriteAnimationComponent.h"

namespace engine { namespace entity { namespace component {

	SpriteAnimationComponent::SpriteAnimationComponent(const std::vector<graphics::SpriteAnimation>& anims)
	{
		for (auto it = anims.begin(); it != anims.end(); ++it)
		{
			animations[it->getName()] = *it;
		}
	}

	SpriteAnimationComponent::SpriteAnimationComponent(const std::initializer_list<graphics::SpriteAnimation>& anims)
	{
		for (auto it = anims.begin(); it != anims.end(); ++it)
		{
			animations[it->getName()] = *it;
		}
	}

	SpriteAnimationComponent::~SpriteAnimationComponent()
	{

	}

} } }