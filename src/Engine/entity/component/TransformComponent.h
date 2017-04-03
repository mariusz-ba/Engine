#pragma once

#include "Component.h"
#include <glm/glm.hpp>

namespace engine { namespace entity { namespace component {

	class TransformComponent : public Component {
	public:
		TransformComponent(const glm::mat4& transformation);
		virtual ~TransformComponent();

		static ComponentType* getStaticType()
		{
			static ComponentType type({ "Transform" });
			return &type;
		}

		inline virtual ComponentType* getType() const override { return getStaticType(); }

	public:
		glm::mat4 transformation;
	};

} } }