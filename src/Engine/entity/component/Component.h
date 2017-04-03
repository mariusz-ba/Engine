#pragma once

#include <string>

namespace engine { namespace entity {
	class Entity;
} }

namespace engine { namespace entity { namespace component {

	struct ComponentType {
		std::string Name;
	};

	class Component {
	public:
		virtual Entity* getEntity() const { return m_Entity; }
		virtual ComponentType* getType() const { return nullptr; }
	protected:
		Entity* m_Entity;
	};

} } }