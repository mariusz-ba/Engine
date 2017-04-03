#include "TransformComponent.h"

namespace engine { namespace entity { namespace component {

	TransformComponent::TransformComponent(const glm::mat4& transformation) :
		transformation(transformation)
	{
	}

	TransformComponent::~TransformComponent()
	{
	}

} } }