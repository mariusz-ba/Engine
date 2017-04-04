#pragma once

#include <vector>
#include "graphics/camera/Camera.h"
#include "graphics/Renderer2D.h"
#include "entity/Entity.h"
#include "entity/component/Components.h"

namespace engine {

	using namespace entity;

	class Scene2D {
	public:
		Scene2D(const glm::mat4& projectionMatrix);
		~Scene2D();

		void add(Entity* entity);

		virtual void onUpdate(float deltaTime);
		virtual void onRender();

		inline graphics::Camera* getCamera() { return m_Camera; }
		inline graphics::Renderer2D* getRenderer() { return m_Renderer; }

	private:
		graphics::Camera* m_Camera;
		graphics::Renderer2D* m_Renderer;
		
		std::vector<Entity*> m_Entities;
	};

}